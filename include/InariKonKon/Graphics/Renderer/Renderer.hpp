#ifndef IKK_RENDERER_HPP
#define IKK_RENDERER_HPP

#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    class Window;
    
    class Renderer
    {
    public:
        enum struct Type : std::uint8_t
        {
            OpenGL, Vulkan
        };

        Renderer() noexcept = default;

        Renderer(const Renderer&) noexcept = default;
        Renderer(Renderer&&) noexcept = default;

        Renderer& operator=(const Renderer&) noexcept = default;
        Renderer& operator=(Renderer&&) noexcept = default;

        virtual ~Renderer() noexcept = default;

        virtual void createContext(const Window& window) const noexcept = 0;

        virtual void registerEntity(const Entity& entity) noexcept = 0;

        virtual void updateUnifromBufferObjects(const Window& window) noexcept = 0;

        virtual void onWindowResize(Vec2u newSize) const noexcept = 0;
        virtual void onFramebufferResize(Vec2u newSize) const noexcept = 0;

        virtual void newFrame(const Color& color) const noexcept = 0;
        virtual void endFrame(const Window& window) const noexcept = 0;

        virtual void draw(const Entity& entity) const noexcept = 0;

        [[nodiscard]] static constexpr std::string_view convertToString(Type type) noexcept;
    private:
    };

    constexpr std::string_view Renderer::convertToString(Type type) noexcept
    {
        switch (type)
        {
        case Renderer::Type::OpenGL:
            return "OpenGL";
        case Renderer::Type::Vulkan:
            return "Vulkan";
        }
    }
}

#endif