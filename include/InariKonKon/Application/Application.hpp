#ifndef IKK_APPLICATION_HPP
#define IKK_APPLICATION_HPP

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Clock.hpp"
#include "InariKonKon/Layer/Layer.hpp"

namespace ikk
{
    class Application final
    {
    public:
        Application(std::u8string_view title, Renderer::Type renderer) noexcept;

        Application(const Application&) noexcept = default;
        Application(Application&&) noexcept = default;

        Application& operator=(const Application&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        ~Application() noexcept = default;

        void run() noexcept;

        [[nodiscard]] const Window& getWindow() const noexcept;
        [[nodiscard]] Window& getWindow() noexcept;
    private:
        Window m_window;
        Clock m_deltaTime = {};
        std::vector<Layer*> m_layers{};

        void handleEvents();
        void update();
        void render() const;

        friend Layer;
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
        return std::format_to(ctx.out(), "ptr: {:#x}", reinterpret_cast<std::uintptr_t>(&application));
    }
};

#endif