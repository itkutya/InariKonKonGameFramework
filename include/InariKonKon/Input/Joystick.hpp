#ifndef IKK_JOYSTICK_HPP
#define IKK_JOYSTICK_HPP

#include <string_view>
#include <cstdint>
#include <utility>

#include "InariKonKon/Utility/NonConstructible.hpp"

namespace ikk
{
    class Joystick final : public NonConstructible
    {
    public:
        using ID = std::uint32_t;

        enum struct Button : std::uint8_t
        {
            Unknown = 0,
            A,
            B,
            X,
            Y,
            LBumper,
            RBumper,
            Back,
            Start,
            Guide,
            LThump,
            RThump,
            Up,
            Down,
            Right,
            Left
        };

        enum struct Axis : std::uint8_t
        {
            Unknown = 0,
            LX,
            LY,
            RX,
            RY,
            LTrigger,
            RTrigger
        };

        enum struct Hat : std::uint8_t
        {
            Unknown,
            Center      = 1 << 0,
            Up          = 1 << 1,
            Right       = 1 << 2,
            Down        = 1 << 3,
            Left        = 1 << 4,
            UpRight     = Up | Right,
            UpLeft      = Up | Left,
            DownRight   = Down | Right,
            DownLeft    = Down | Left
        };

        [[nodiscard]] static constexpr std::string_view convertToString(Button button) noexcept;
        [[nodiscard]] static constexpr std::string_view convertToString(Axis axis) noexcept;
        [[nodiscard]] static constexpr std::string_view convertToString(Hat hat) noexcept;
    private:
        [[nodiscard]] static Button convertFromGLFWButton(std::int32_t button) noexcept;
        [[nodiscard]] static Axis convertFromGLFWAxis(std::int32_t axis) noexcept;
        [[nodiscard]] static Hat convertFromGLFWHat(std::int32_t hat) noexcept;

        [[nodiscard]] static std::int32_t convertToGLFWButton(Button button) noexcept;
        [[nodiscard]] static std::int32_t convertToGLFWAxis(Axis axis) noexcept;
        [[nodiscard]] static std::int32_t convertToGLFWHat(Hat hat) noexcept;

        friend class EventCallbackFuncs;
        friend class PhysicalJoystick;
    };

    constexpr std::string_view Joystick::convertToString(Button button) noexcept
    {
        switch (button)
        {
        case Button::Unknown:   return "Unknown";
        case Button::A:         return "A";
        case Button::B:         return "B";
        case Button::X:         return "X";
        case Button::Y:         return "Y";
        case Button::LBumper:   return "Left Bumper";
        case Button::RBumper:   return "Right Bumper";
        case Button::Back:      return "Back";
        case Button::Start:     return "Start";
        case Button::Guide:     return "Guide";
        case Button::LThump:    return "Left Thump";
        case Button::RThump:    return "Right Thump";
        case Button::Up:        return "DPAD Up";
        case Button::Down:      return "DPAD Down";
        case Button::Right:     return "DPAD Right";
        case Button::Left:      return "DPAD Left";
        }
        return "Unknown";
    }

    constexpr std::string_view Joystick::convertToString(Axis axis) noexcept
    {
        switch (axis)
        {
        case Axis::Unknown:     return "Unknown";
        case Axis::LX:          return "Left X";
        case Axis::LY:          return "Left Y";
        case Axis::RX:          return "Right X";
        case Axis::RY:          return "Right Y";
        case Axis::LTrigger:    return "Left Trigger";
        case Axis::RTrigger:    return "Right Trigger";
        }
        return "Unknown";
    }

    constexpr std::string_view Joystick::convertToString(Hat hat) noexcept
    {
        switch (hat)
        {
        case Hat::Unknown:      return "Unknown";
        case Hat::Center:       return "Centered";
        case Hat::Up:           return "Up";
        case Hat::Right:        return "Right";
        case Hat::Down:         return "Down";
        case Hat::Left:         return "Left";
        case Hat::UpRight:      return "Up & Right";
        case Hat::UpLeft:       return "Up & Left";
        case Hat::DownRight:    return "Down & Right";
        case Hat::DownLeft:     return "Down & Left";
        }
        return "Unknown";
    }

    constexpr Joystick::Hat operator|(Joystick::Hat lhs, Joystick::Hat rhs) noexcept
    {
        return static_cast<Joystick::Hat>(std::to_underlying(lhs) | std::to_underlying(rhs));
    }

    constexpr Joystick::Hat operator&(Joystick::Hat lhs, Joystick::Hat rhs) noexcept
    {
        return static_cast<Joystick::Hat>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }
}

#endif