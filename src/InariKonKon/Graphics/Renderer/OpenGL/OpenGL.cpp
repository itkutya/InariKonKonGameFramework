#include "InariKonKon/Graphics/Renderer/OpenGL/OpenGL.hpp"

#include <cstddef>

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
    }

    /*
    template<typename VertexT>
    struct VertexTraits;

    template<class VecType, class... Attributes>
    struct VertexTraits<VertexBase<VecType, Attributes...>>
    {
        using VertexType = VertexBase<VecType, Attributes...>;

        static constexpr size_t stride = sizeof(VertexType);

        static constexpr bool hasColor = HasAttribute<Color, Attributes...>::value;
        static constexpr bool hasNormal = HasAttribute<Vec2f, Attributes...>::value;

        static constexpr size_t positionOffset = offsetof(VertexType, position);
        static constexpr size_t colorOffset = hasColor ? offsetof(VertexType, color) : 0;
        static constexpr size_t normalOffset = hasNormal ? offsetof(VertexType, normal) : 0;
    };

    template<class VertexT>
    void setupVertexAttribs()
    {
        constexpr auto stride = VertexTraits<VertexT>::stride;

        glCheck(glEnableVertexAttribArray(0));
        glCheck(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)VertexTraits<VertexT>::positionOffset));

        if constexpr (VertexTraits<VertexT>::hasColor)
        {
            glCheck(glEnableVertexAttribArray(1));
            glCheck(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*)VertexTraits<VertexT>::colorOffset));
        }

        if constexpr (VertexTraits<VertexT>::hasNormal)
        {
            glCheck(glEnableVertexAttribArray(2));
            glCheck(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)VertexTraits<VertexT>::normalOffset));
        }
    }
    */

    void OpenGL::registerEntity(const Entity& entity) noexcept
    {
        if (std::find_if(this->m_objects.begin(), this->m_objects.end(), this->matchEntity(entity)) != this->m_objects.end())
            return;

        OpenGLObject temp{};

        const Drawable* drawable = entity.getComponent<Drawable>().value();

        const Model& model = drawable->getModel();
        const std::vector<std::byte>& vertices = model.getRawVertexBuffer();
        const std::vector<std::uint32_t>& indices = model.getIndices();

        if (vertices.empty() == true)
            return;

        glCheck(glGenVertexArrays(1, &temp.VAO));
        glCheck(glGenBuffers(1, &temp.VBO));
        glCheck(glGenBuffers(1, &temp.EBO));

        glCheck(glBindVertexArray(temp.VAO));

        glCheck(glBindBuffer(GL_ARRAY_BUFFER, temp.VBO));
        glCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.at(0), GL_STATIC_DRAW));

        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp.EBO));
        glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t), &indices.at(0), GL_STATIC_DRAW));

        //
        glCheck(glEnableVertexAttribArray(0));
        glCheck(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, model.getVertexStride(), (void*)offsetof(UIVertex, position)));

        glCheck(glEnableVertexAttribArray(1));
        glCheck(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, model.getVertexStride(), (void*)offsetof(UIVertex, color)));
        //
        //setupVertexAttribs<std::remove_cvref<decltype(vertices)>::type::value_type>();

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

        //TEMP
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        const Drawable* drawable = entity.getComponent<Drawable>().value();
        glCheck(glBindVertexArray(it->second.VAO));
        glCheck(glDrawElements(GL_TRIANGLES, drawable->getModel().getIndices().size(), GL_UNSIGNED_INT, 0));
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