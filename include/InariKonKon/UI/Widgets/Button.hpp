#ifndef IKK_BUTTON_HPP
#define IKK_BUTTON_HPP

#include <string>

#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/UI/UI.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] Button final : public UI
    {
    public:
        enum struct State : std::uint8_t
        {
            Pressed, Held, None
        };

        [[nodiscard]] Button(std::string_view text, Vec2f position = {}, Vec2f size = { 1, 1 }, Degreef rotation = {}, Color color = Color::White, float radius = 0.0f) noexcept;
        [[nodiscard]] Button(std::string_view text, Vec2f position = {}, Vec2f size = { 1, 1 }, Radianf rotation = {}, Color color = Color::White, float radius = 0.0f) noexcept;

        Button(const Button&) noexcept = default;
        Button(Button&&) noexcept = default;

        Button& operator=(const Button&) noexcept = default;
        Button& operator=(Button&&) noexcept = default;

        ~Button() noexcept = default;

        [[nodiscard]] const State& getState() const noexcept;

        [[nodiscard]] bool isPressed() const noexcept;
    private:
        State m_state = State::None;
        std::string m_text{};
    };
}

#endif