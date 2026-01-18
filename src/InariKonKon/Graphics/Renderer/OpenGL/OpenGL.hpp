#pragma once

#include <unordered_map>

#include "InariKonKon/Graphics/Renderer/Renderer.hpp"

namespace ikk
{
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

        void registerEntity(const Drawable& entity) noexcept override;

        void updateUnifromBufferObjects(const Window& window) noexcept override;

        void onWindowResize(Vec2u newSize) const noexcept override;
        void onFramebufferResize(Vec2u newSize) const noexcept override;

        void draw(const Drawable& entity) const noexcept override;

        void newFrame(const Color& color) const noexcept override;
        void endFrame(const Window& window) const noexcept override;
    private:
        std::unordered_map<const Drawable*, OpenGLObject> m_objects = {};
        std::unordered_map<const Camera*, CameraUniformBufferObject> m_ubos = {};
    };
}