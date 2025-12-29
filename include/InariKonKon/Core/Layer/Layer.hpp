#ifndef IKK_LAYERS_HPP
#define IKK_LAYERS_HPP

#include <type_traits>
#include <cstdint>
#include <format>

namespace ikk
{
    class Application;
    class Window;
    class Event;
    class Time;
    
    class Layer
    {
    public:
        using IDType = std::uint32_t;

        Layer() noexcept;

        Layer(const Layer& other) noexcept;
        Layer(Layer&& other) noexcept;

        Layer& operator=(const Layer& other) noexcept;
        Layer& operator=(Layer&& other) noexcept;

        virtual ~Layer() noexcept;

        virtual void attach(Application& app) noexcept final;
        virtual void detach() noexcept final;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;

        virtual const IDType& getID() const noexcept final;
    private:
        IDType m_id = 0;
        Application* m_app = nullptr;
    };

    template<class T>
    concept LayerType = std::is_base_of<Layer, T>::value;
}

template<>
class std::formatter<ikk::Layer>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Layer& layer, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "id: {}", layer.getID());
    }
};

#endif