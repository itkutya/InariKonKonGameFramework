#ifndef IKK_APPLICATION_HPP
#define IKK_APPLICATION_HPP

#include <string_view>

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Clock.hpp"

namespace ikk
{
    class Application
    {
    public:
        virtual ~Application() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;

        virtual void run() noexcept final;

        [[nodiscard]] virtual const Window& getWindow() const noexcept final;
        [[nodiscard]] virtual Window& getWindow() noexcept final;
    protected:
        Application(std::u8string_view title, Renderer::Type renderer) noexcept;

        Application(const Application&) noexcept = default;
        Application(Application&&) noexcept = default;

        Application& operator=(const Application&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;
    private:
        Window m_window;
        
        Clock m_deltaTime = {};

        void handleEvents();
        void update();
        void render() const;
    };
}

template<>
class std::formatter<ikk::Application>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Application& application, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "ptr: {}", reinterpret_cast<std::uintptr_t>(&application));
    }
};

#endif