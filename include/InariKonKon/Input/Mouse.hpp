#ifndef IKK_MOUSE_HPP
#define IKK_MOUSE_HPP

#include <string_view>

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    class Window;

    class Mouse final : public NonConstructible
    {
    public:
        enum struct Button : std::uint8_t
        {
            Unknown = 0,
            Left,
            Right,
            Middle,
            Extra1,
            Extra2,
            Extra3,
            Extra4,
            Extra5
        };

        enum struct Wheel : std::uint8_t
        {
            Unknown = 0,
            Horizontal,
            Vertical
        };

        [[nodiscard]] static Vec2d getCursorPosition(const Window& window) noexcept;

        [[nodiscard]] static constexpr std::string_view convertToString(Button button) noexcept;
        [[nodiscard]] static constexpr std::string_view convertToString(Wheel wheel) noexcept;
    private:
        [[nodiscard]] static std::int32_t convertToGLFWButton(Button button) noexcept;
        [[nodiscard]] static Button convertFromGLFWButton(std::int32_t button) noexcept;

        friend class InputManager;
        friend class EventCallbackFuncs;
    };

    constexpr std::string_view Mouse::convertToString(Button button) noexcept
    {
        switch (button)
        {
            case Button::Unknown:   return "Unknown";
            case Button::Left:      return "Left";
            case Button::Right:     return "Right";
            case Button::Middle:    return "Middle";
            case Button::Extra1:    return "Extra 1";
            case Button::Extra2:    return "Extra 2";
            case Button::Extra3:    return "Extra 3";
            case Button::Extra4:    return "Extra 4";
            case Button::Extra5:    return "Extra 5";
        }
        return "Unknown";
    }

    constexpr std::string_view Mouse::convertToString(Wheel wheel) noexcept
    {
        switch (wheel)
        {
            case Wheel::Unknown:    return "Unknown";
            case Wheel::Vertical:   return "Vertical";
            case Wheel::Horizontal: return "Horizontal";
        }
        return "Unknown";
    }
}

#endif