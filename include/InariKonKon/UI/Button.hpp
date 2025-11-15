#ifndef IKK_BUTTON_HPP
#define IKK_BUTTON_HPP

#include "InariKonKon/ECS/Entities/Entity.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] Button final : public Entity
    {
    public:
        enum struct State : std::uint8_t
        {
            Pressed, Held, None
        };

        [[nodiscard]] Button(const Window& window) noexcept;

        Button(const Button&) noexcept = default;
        Button(Button&&) noexcept = default;

        Button& operator=(const Button&) noexcept = default;
        Button& operator=(Button&&) noexcept = default;

        ~Button() noexcept = default;

        [[nodiscard]] const State& getState() const noexcept;

        [[nodiscard]] bool isPressed() const noexcept;
    private:
        State m_state = State::None;
    };
}

#endif