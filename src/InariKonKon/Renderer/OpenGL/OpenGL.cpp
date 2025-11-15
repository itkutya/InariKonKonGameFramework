#include "InariKonKon/Renderer/OpenGL/OpenGL.hpp"

#include <cstddef>

#include "glad/gl.h"

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Log.hpp"

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
        glViewport(0, 0, window.getSettings().videomode.width, window.getSettings().videomode.height);
    }

    void OpenGL::registerEntity(const Entity& entity, const Drawable& drawable) noexcept
    {
        const auto it = std::find_if(this->m_objects.begin(), this->m_objects.end(),
            [&entity](const std::pair<const Entity*, OpenGLObject>& pair) noexcept
            {
                return pair.first == &entity;
            });

        if (it != this->m_objects.end())
            return;

        OpenGLObject temp{};

        const Model* model = drawable.getModel();
        const std::vector<Vertex>& vertices = model->m_vertices;
        const std::vector<std::uint32_t>& indices = model->m_indices;

        //TODO:
        //Make this generic...
        glGenVertexArrays(1, &temp.VAO);
        glGenBuffers(1, &temp.VBO);
        glGenBuffers(1, &temp.EBO);

        glBindVertexArray(temp.VAO);

        glBindBuffer(GL_ARRAY_BUFFER, temp.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.at(0), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t), &indices.at(0), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

        glBindVertexArray(0);

        temp.shaderProgramID = glCreateProgram();
        glAttachShader(temp.shaderProgramID, drawable.getVertexShader()->getID());
        glAttachShader(temp.shaderProgramID, drawable.getFragmentShader()->getID());
        glLinkProgram(temp.shaderProgramID);

        std::int32_t success = 0;
        glGetProgramiv(temp.shaderProgramID, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            char infoLog[1024] = {};
            glGetProgramInfoLog(temp.shaderProgramID, 1024, NULL, infoLog);
            DEBUG_LOG(Log::Level::Error, "Shader program linking failed:\n\tinfo: {}", infoLog);
            glDeleteProgram(temp.shaderProgramID);
        }

        this->m_objects.emplace_back(&entity, std::move(temp));
    }

    void OpenGL::onWindowResize(Vec2u newSize) const noexcept
    {
    }

    void OpenGL::onFramebufferResize(Vec2u newSize) const noexcept
    {
        glViewport(0, 0, newSize.x(), newSize.y());
    }

    void OpenGL::draw(const Entity& entity, const Drawable& drawable, const Transform3D& transform) const noexcept
    {
        const auto it = std::find_if(this->m_objects.begin(), this->m_objects.end(),
            [&entity](const std::pair<const Entity*, OpenGLObject>& pair) noexcept
            {
                return pair.first == &entity;
            });

        if (it == this->m_objects.end())
            return;

        const Model* model = drawable.getModel();
        const std::vector<std::uint32_t>& indices = model->m_indices;
        const std::uint32_t shaderID = it->second.shaderProgramID;

        auto projectionMatrix = drawable.getCamera()->getProjectionMatrix(1024.f / 800.f);

        glUseProgram(shaderID);

        glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_TRUE, &transform.getWorldMatrix().at(0, 0));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_TRUE, &drawable.getCamera()->getViewMatrix().at(0, 0));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_TRUE, &projectionMatrix.at(0, 0));

        glBindVertexArray(it->second.VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    void OpenGL::newFrame(const Color& color) const noexcept
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGL::endFrame(const Window& window) const noexcept
    {
        glfwSwapBuffers(window.m_window);
    }
}