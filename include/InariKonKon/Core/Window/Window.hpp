#ifndef IKK_WINDOW_HPP
#define IKK_WINDOW_HPP

#include <expected>
#include <memory>
#include <stack>

#include "InariKonKon/Graphics/Renderer/Renderer.hpp"
#include "InariKonKon/Core/Monitor/VideoMode.hpp"
#include "InariKonKon/Core/Event/Event.hpp"
#include "InariKonKon/Math/Rect.hpp"

struct GLFWwindow;

namespace ikk
{
    class [[nodiscard]] Window final
    {
    public:
        struct [[nodiscard]] Settings
        {
            Renderer::Type renderer = Renderer::Type::OpenGL;
            std::u8string_view title = {};
            VideoMode videomode = {};
            bool fullscreen = false;
            bool enableRawMouseInput = false;
            Color clearColor = Color::CornflowerBlue;
        };

        [[nodiscard]] Window(Settings settings) noexcept;

        Window(const Window& other) noexcept;
        Window(Window&& other) noexcept;

        Window& operator=(const Window& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        ~Window() noexcept;

        [[nodiscard]] virtual const Settings& getSettings() const noexcept final;
        [[nodiscard]] virtual Settings& getSettings() noexcept final;

        [[nodiscard]] const Vec2f& getContentScale() const noexcept;
        [[nodiscard]] const float getAscpectRation() const noexcept;
        [[nodiscard]] const Rectf getViewport() const noexcept;
        [[nodiscard]] const std::shared_ptr<Renderer>& getRenderer() const noexcept;

        void lockMouse(bool value) noexcept;

        void draw(const Entity& entity) const noexcept;
    private:
        Settings m_settings = {};

        GLFWwindow* m_window = nullptr;
        std::shared_ptr<Renderer> m_renderer = nullptr;

        std::stack<Event> m_eventStack = {};

        Vec2f m_contentScale = {};

        bool shouldClose() const noexcept;

        void pollEvents() noexcept;

        void beginRender() const noexcept;
        void endRender() const noexcept;

        [[nodiscard]] std::expected<GLFWwindow*, Error> createWindow(const Settings& settings) noexcept;

        void setupWindow() noexcept;

        void copy(const Window& other) noexcept;
        void move(Window&& other) noexcept;

        friend class EventCallbackFuncs;
        friend class InputManager;
        friend class Application;
        friend class OpenGL;
        friend Mouse;
    };
}

template<>
class std::formatter<ikk::Window::Settings>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Window::Settings& settings, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "renderer type: {}\n\ttitle: {}\n\tvideomode: {}\n\tfullscreen: {}\n\traw input: {}\n\tclear color: {}",
            ikk::Renderer::convertToString(settings.renderer), TO_ANSI(settings.title.data()), settings.videomode,
            settings.fullscreen, settings.enableRawMouseInput, settings.clearColor);
    }
};

template<>
class std::formatter<ikk::Window>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Window& window, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "ptr: {:#x}\n\tsettings: {}",
            reinterpret_cast<std::uintptr_t>(&window), window.getSettings());
    }
};

#endif