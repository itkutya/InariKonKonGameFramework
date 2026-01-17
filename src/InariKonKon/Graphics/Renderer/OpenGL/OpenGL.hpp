#pragma once

#include <utility>

#include "InariKonKon/Graphics/Renderer/Renderer.hpp"

namespace ikk
{
    class Entity;
    class Camera;

    class [[nodiscard]] OpenGL final : public Renderer
    {
        struct OpenGLObject
        {
            std::uint32_t VAO = 0;
            std::uint32_t VBO = 0;
            std::uint32_t EBO = 0;

            std::uint32_t textureID = 0;
        };

        struct CameraUniformBufferObject
        {
            std::uint32_t UBO = 0;
            bool ignoreZ = false;
        };
    public:
        [[nodiscard]] OpenGL() noexcept;

        OpenGL(const OpenGL&) noexcept = default;
        OpenGL(OpenGL&&) noexcept = default;

        OpenGL& operator=(const OpenGL&) noexcept = default;
        OpenGL& operator=(OpenGL&&) noexcept = default;

        ~OpenGL() noexcept = default;

        void createContext(const Window& window) const noexcept override;

        void registerEntity(const Entity& entity) noexcept override;

        void updateUnifromBufferObjects(const Window& window) noexcept override;

        void onWindowResize(Vec2u newSize) const noexcept override;
        void onFramebufferResize(Vec2u newSize) const noexcept override;

        void draw(const Entity& entity) const noexcept override;

        void newFrame(const Color& color) const noexcept override;
        void endFrame(const Window& window) const noexcept override;
    private:
        std::vector<std::pair<const Entity*, OpenGLObject>> m_objects = {};
        std::vector<std::pair<const Camera*, CameraUniformBufferObject>> m_ubos = {};

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