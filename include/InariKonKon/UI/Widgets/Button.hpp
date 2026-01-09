#ifndef IKK_BUTTON_HPP
#define IKK_BUTTON_HPP

#include <string>

#include "InariKonKon/Core/Event/EventListener.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/UI/UI.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] Button final : public UI, public EventListener<MouseEvent::Button>, public EventListener<MouseEvent::Move>
    {
    public:
        enum struct State : std::uint8_t
        {
            Pressed, Held, Withheld, None
        };

        [[nodiscard]] Button(std::string_view text, Vec2f position = {}, Vec2f size = { 1, 1 }, Degreef rotation = {}, Color color = Color::White, float radius = 0.0f) noexcept;

        Button(const Button&) noexcept = default;
        Button(Button&&) noexcept = default;

        Button& operator=(const Button&) noexcept = default;
        Button& operator=(Button&&) noexcept = default;

        ~Button() noexcept = default;

        [[nodiscard]] const State& getState() const noexcept;

        [[nodiscard]] bool isPressed() const noexcept;
    private:
        std::string m_text{};
        State m_state = State::None;
        State m_prevState = State::None;
        bool m_hovered = false;

        void onNotify(const MouseEvent::Button& event) noexcept override;
        void onNotify(const MouseEvent::Move& event) noexcept override;
    };
}

#endif