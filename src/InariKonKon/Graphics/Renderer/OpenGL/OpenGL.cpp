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
        //Put it into UI or something...
        glCheck(glEnable(GL_BLEND));
        glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void OpenGL::registerEntity(const Entity& entity) noexcept
    {
        if (std::find_if(this->m_objects.begin(), this->m_objects.end(), this->matchEntity(entity)) != this->m_objects.end())
            return;

        const Drawable* drawable = entity.getComponent<Drawable>().value();

        const Model& model = drawable->getModel();
        const std::vector<std::byte>& vertices = model.getRawVertexBuffer();

        if (vertices.empty() == true)
            return;

        OpenGLObject temp{};

        glCheck(glGenVertexArrays(1, &temp.VAO));
        glCheck(glBindVertexArray(temp.VAO));

        glCheck(glGenBuffers(1, &temp.VBO));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, temp.VBO));
        glCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.at(0), GL_STATIC_DRAW));

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
                case VertexAttribute::Type::Float:
                    return GL_FLOAT;
                case VertexAttribute::Type::Double:
                    return GL_DOUBLE;
                case VertexAttribute::Type::Int8:
                    return GL_BYTE;
                case VertexAttribute::Type::UInt8:
                    return GL_UNSIGNED_BYTE;
                case VertexAttribute::Type::Int16:
                    return GL_SHORT;
                case VertexAttribute::Type::UInt16:
                    return GL_UNSIGNED_SHORT;
                case VertexAttribute::Type::Int32:
                    return GL_INT;
                case VertexAttribute::Type::UInt32:
                    return GL_UNSIGNED_INT;
                }
                return 0;
            };

            const VertexAttribute& attribute = attributes.at(i);
            glCheck(glEnableVertexAttribArray(i));
            glCheck(glVertexAttribPointer(i, attribute.count, convertToOpenGLType(attribute.type),
                attribute.normalized, model.getVertexStride(), (const void*)attribute.offset));
        }

        glCheck(glBindVertexArray(0));

        this->m_objects.emplace_back(&entity, std::move(temp));
    }

    void OpenGL::onWindowResize(Vec2u newSize) const noexcept
    {
    }

    void OpenGL::onFramebufferResize(Vec2u newSize) const noexcept
    {
        glCheck(glViewport(0, 0, newSize.x(), newSize.y()));
    }

    void OpenGL::draw(const Entity& entity) const noexcept
    {
        const auto it = std::find_if(this->m_objects.begin(), this->m_objects.end(), this->matchEntity(entity));

        if (it == this->m_objects.end())
            return;

        const Drawable* drawable = entity.getComponent<Drawable>().value();
        const std::vector<std::uint32_t>& indices = drawable->getModel().getIndices();
        glCheck(glBindVertexArray(it->second.VAO));
        if (indices.empty() == true)
        {
            const std::size_t verticesCount = drawable->getModel().getRawVertexBuffer().size() / drawable->getModel().getVertexStride();
            glCheck(glDrawArrays(GL_TRIANGLES, 0, verticesCount));
        }
        else
        {
            glCheck(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
        }
    }

    void OpenGL::newFrame(const Color& color) const noexcept
    {
        glCheck(glClearColor(color.r, color.g, color.b, color.a));
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
    }

    void OpenGL::endFrame(const Window& window) const noexcept
    {
        glfwSwapBuffers(window.m_window);
    }
}