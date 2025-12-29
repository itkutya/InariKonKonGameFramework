#ifndef IKK_OPENGL_HPP
#define IKK_OPENGL_HPP

#include <utility>

#include "InariKonKon/Graphics/Renderer/Renderer.hpp"

namespace ikk
{
    class Entity;

    class [[nodiscard]] OpenGL final : public Renderer
    {
        struct OpenGLObject
        {
            std::uint32_t VAO = 0;
            std::uint32_t VBO = 0;
            std::uint32_t EBO = 0;
        };
    public:
        [[nodiscard]] OpenGL() noexcept;

        OpenGL(const OpenGL&) noexcept = default;
        OpenGL(OpenGL&&) noexcept = default;

        OpenGL& operator=(const OpenGL&) noexcept = default;
        OpenGL& operator=(OpenGL&&) noexcept = default;

        ~OpenGL() noexcept = default;

        void createContext(const Window& window) const noexcept override;

        void registerEntity(const Entity& entity, const Drawable& drawable) noexcept override;

        void onWindowResize(Vec2u newSize) const noexcept override;
        void onFramebufferResize(Vec2u newSize) const noexcept override;

        void draw(const Entity& entity, const Drawable& drawable) const noexcept override;

        void newFrame(const Color& color) const noexcept override;
        void endFrame(const Window& window) const noexcept override;
    private:
        std::vector<std::pair<const Entity*, OpenGLObject>> m_objects = {};

        constexpr auto matchEntity(const Entity& entity) const noexcept;
    };

    constexpr auto OpenGL::matchEntity(const Entity& entity) const noexcept
    {
        return [&entity](const std::pair<const Entity*, OpenGLObject>& pair) noexcept -> bool
        {
            return pair.first == &entity;
        };
    }
}

#endif