#include "InariKonKon/Graphics/Renderer/OpenGL/OpenGL.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp"
#include "InariKonKon/Core/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/Core/Window/Window.hpp"

namespace ikk
{
    OpenGL::OpenGL() noexcept
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    void OpenGL::createContext(const Window& window) const noexcept
    {
        glfwMakeContextCurrent(window.m_window);
        const int version = gladLoadGL(glfwGetProcAddress);
        DEBUG_LOG("OpenGL version: {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        glCheck(glViewport(0, 0, window.getSettings().videomode.width, window.getSettings().videomode.height));

        //TEMP
        //TODO:
        glCheck(glEnable(GL_STENCIL_TEST));
        glCheck(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
        glCheck(glDisable(GL_DEPTH_TEST));
        glCheck(glEnable(GL_BLEND));
        glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void OpenGL::registerEntity(const Drawable& entity) noexcept
    {
        if (this->m_objects.contains(&entity) == true)
            return;

        const Model& model = entity.getModel();
        const std::vector<std::byte>& vertices = model.getRawVertexBuffer();

        if (vertices.empty() == true)
            return;

        OpenGLObject temp{};

        glCheck(glGenVertexArrays(1, &temp.VAO));
        glCheck(glBindVertexArray(temp.VAO));

        glCheck(glGenBuffers(1, &temp.VBO));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, temp.VBO));
        glCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.at(0), GL_DYNAMIC_DRAW));

        const std::vector<std::uint32_t>& indices = model.getIndices();
        if (indices.size() != 0)
        {
            glCheck(glGenBuffers(1, &temp.EBO));
            glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp.EBO));
            glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t), &indices.at(0), GL_STATIC_DRAW));
        }

        const std::vector<VertexAttribute>& attributes = model.getVertexAttributes();
        for (std::size_t i = 0; i < attributes.size(); ++i)
        {
            static constexpr auto convertToOpenGLType = [](VertexAttribute::Type type) noexcept
            {
                switch (type)
                {
                case VertexAttribute::Type::Float:  return GL_FLOAT;
                case VertexAttribute::Type::Double: return GL_DOUBLE;
                case VertexAttribute::Type::Int8:   return GL_BYTE;
                case VertexAttribute::Type::UInt8:  return GL_UNSIGNED_BYTE;
                case VertexAttribute::Type::Int16:  return GL_SHORT;
                case VertexAttribute::Type::UInt16: return GL_UNSIGNED_SHORT;
                case VertexAttribute::Type::Int32:  return GL_INT;
                case VertexAttribute::Type::UInt32: return GL_UNSIGNED_INT;
                }
                return 0;
            };

            const VertexAttribute& attribute = attributes.at(i);
            glCheck(glEnableVertexAttribArray(i));
            glCheck(glVertexAttribPointer(i, attribute.count, convertToOpenGLType(attribute.type),
                attribute.normalized, model.getVertexStride(), (const void*)attribute.offset));
        }

        glCheck(glBindVertexArray(0));

        //TODO: glCheck()
        const Camera& camera = entity.getCamera();
        if (this->m_ubos.contains(&camera) == false)
        {
            CameraUniformBufferObject object{};
            glGenBuffers(1, &object.UBO);
            glBindBuffer(GL_UNIFORM_BUFFER, object.UBO);
            glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Mat4x4f), NULL, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            const ShaderProgram& shader = entity.getShaderProgram();

            glUniformBlockBinding(shader.getID(),
                glGetUniformBlockIndex(shader.getID(), "CameraMatrices"), 0);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, object.UBO);

            //TODO:
            object.ignoreZ = true;

            this->m_ubos.emplace(&camera, std::move(object));
        }

        //TODO: glCheck()
        const Texture* texture = entity.getTexture();
        if (texture != nullptr)
        {
            if (texture->getBytesPerPixel() == 1)
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &temp.textureID);
            //TODO:
            //activate texture binding spot as well
            //TODO:
            glBindTexture(GL_TEXTURE_2D, temp.textureID);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED, //TODO:
                texture->getWidth(),
                texture->getHeight(),
                0,
                GL_RED, //TODO:
                GL_UNSIGNED_BYTE,
                texture->getBuffer().data()
            );

            //TODO:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        this->m_objects.emplace(&entity, std::move(temp));
    }

    void OpenGL::updateUnifromBufferObjects(const Window& window) noexcept
    {
        for (const auto& [camera, object] : this->m_ubos)
        {
            glCheck(glBindBuffer(GL_UNIFORM_BUFFER, object.UBO));
            if (object.ignoreZ == true)
            {
                const auto projectionMatrix = camera->getProjectionMatrix(window.getViewport()).convertTo<MatrixOrdering::ColumnMajor>();
                glCheck(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4x4f), &projectionMatrix.at(0, 0)));
            }
            else
            {
                const auto projectionMatrix = camera->getProjectionMatrix(window.getAscpectRation()).convertTo<MatrixOrdering::ColumnMajor>();
                glCheck(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4x4f), &projectionMatrix.at(0, 0)));
            }

            const auto viewMatrix = camera->getViewMatrix().convertTo<MatrixOrdering::ColumnMajor>();
            glCheck(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4x4f), sizeof(Mat4x4f), &viewMatrix.at(0, 0)));
            glCheck(glBindBuffer(GL_UNIFORM_BUFFER, 0));
        }
    }

    void OpenGL::onWindowResize(Vec2u newSize) const noexcept
    {
    }

    void OpenGL::onFramebufferResize(Vec2u newSize) const noexcept
    {
        glCheck(glViewport(0, 0, newSize.x(), newSize.y()));
    }

    void OpenGL::draw(const Drawable& entity) const noexcept
    {
        if (this->m_objects.contains(&entity) == false) //TODO: ERROR REPORT, register entity first --> call window.draw(entity);
            return;

        const OpenGLObject& object = this->m_objects.at(&entity);

        glCheck(glStencilFunc(GL_ALWAYS, 1, 0xFF));
        glCheck(glStencilMask(0xFF));

        const Model& model = entity.getModel();
        if (model.isDirty() == true)
        {
            const std::vector<std::byte>& vertices = model.getRawVertexBuffer();
            glCheck(glBindBuffer(GL_ARRAY_BUFFER, object.VBO));
            glCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.at(0), GL_DYNAMIC_DRAW));
            model.setDirty(false);
        }

        entity.getShaderProgram().activate();

        //
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, object.textureID);
        //

        glCheck(glBindVertexArray(object.VAO));
        const std::vector<std::uint32_t>& indices = entity.getModel().getIndices();
        if (indices.size() > 0)
        {
            glCheck(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
        }
        else
        {
            glCheck(glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount()));
        }
    }

    void OpenGL::newFrame(const Color& color) const noexcept
    {
        glCheck(glClearColor(color.r, color.g, color.b, color.a));
        glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void OpenGL::endFrame(const Window& window) const noexcept
    {
        glfwSwapBuffers(window.m_window);
    }
}