#include "InariKonKon/Input/Joystick.hpp"

#include "InariKonKon/Core/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep

namespace ikk
{
    Joystick::Button Joystick::convertFromGLFWButton(std::int32_t button) noexcept
    {
        switch (button)
        {
        case GLFW_GAMEPAD_BUTTON_A:             return Button::A;
        case GLFW_GAMEPAD_BUTTON_B:             return Button::B;
        case GLFW_GAMEPAD_BUTTON_X:             return Button::X;
        case GLFW_GAMEPAD_BUTTON_Y:             return Button::Y;
        case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:   return Button::LBumper;
        case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:  return Button::RBumper;
        case GLFW_GAMEPAD_BUTTON_BACK:          return Button::Back;
        case GLFW_GAMEPAD_BUTTON_START:         return Button::Start;
        case GLFW_GAMEPAD_BUTTON_GUIDE:         return Button::Guide;
        case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:    return Button::LThump;
        case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:   return Button::RThump;
        case GLFW_GAMEPAD_BUTTON_DPAD_UP:       return Button::Up;
        case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:     return Button::Down;
        case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:    return Button::Right;
        case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:     return Button::Left;
        }
        return Button::Unknown;
    }

    Joystick::Axis Joystick::convertFromGLFWAxis(std::int32_t axis) noexcept
    {
        switch (axis)
        {
        case GLFW_GAMEPAD_AXIS_LEFT_X:          return Axis::LX;
        case GLFW_GAMEPAD_AXIS_LEFT_Y:          return Axis::LY;
        case GLFW_GAMEPAD_AXIS_RIGHT_X:         return Axis::RX;
        case GLFW_GAMEPAD_AXIS_RIGHT_Y:         return Axis::RY;
        case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:    return Axis::LTrigger;
        case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:   return Axis::RTrigger;
        }
        return Axis::Unknown;
    }

    Joystick::Hat Joystick::convertFromGLFWHat(std::int32_t hat) noexcept
    {
        switch (hat)
        {
        case GLFW_HAT_CENTERED:     return Hat::Center;
        case GLFW_HAT_UP:           return Hat::Up;
        case GLFW_HAT_RIGHT:        return Hat::Right;
        case GLFW_HAT_DOWN:         return Hat::Down;
        case GLFW_HAT_LEFT:         return Hat::Left;
        case GLFW_HAT_RIGHT_UP:     return Hat::UpRight;
        case GLFW_HAT_LEFT_UP:      return Hat::UpLeft;
        case GLFW_HAT_RIGHT_DOWN:   return Hat::DownRight;
        case GLFW_HAT_LEFT_DOWN:    return Hat::DownLeft;
        }
        return Hat::Unknown;
    }

    std::int32_t Joystick::convertToGLFWButton(Button button) noexcept
    {
        switch (button)
        {
        case Button::Unknown:   return GLFW_KEY_UNKNOWN;
        case Button::A:         return GLFW_GAMEPAD_BUTTON_A;
        case Button::B:         return GLFW_GAMEPAD_BUTTON_B;
        case Button::X:         return GLFW_GAMEPAD_BUTTON_X;
        case Button::Y:         return GLFW_GAMEPAD_BUTTON_Y;
        case Button::LBumper:   return GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;
        case Button::RBumper:   return GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;
        case Button::Back:      return GLFW_GAMEPAD_BUTTON_BACK;
        case Button::Start:     return GLFW_GAMEPAD_BUTTON_START;
        case Button::Guide:     return GLFW_GAMEPAD_BUTTON_GUIDE;
        case Button::LThump:    return GLFW_GAMEPAD_BUTTON_LEFT_THUMB;
        case Button::RThump:    return GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;
        case Button::Up:        return GLFW_GAMEPAD_BUTTON_DPAD_UP;
        case Button::Down:      return GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
        case Button::Right:     return GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;
        case Button::Left:      return GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
        }
        return GLFW_KEY_UNKNOWN;
    }

    std::int32_t Joystick::convertToGLFWAxis(Axis axis) noexcept
    {
        switch (axis)
        {
        case Axis::Unknown:     return GLFW_KEY_UNKNOWN;
        case Axis::LX:          return GLFW_GAMEPAD_AXIS_LEFT_X;
        case Axis::LY:          return GLFW_GAMEPAD_AXIS_LEFT_Y;
        case Axis::RX:          return GLFW_GAMEPAD_AXIS_RIGHT_X;
        case Axis::RY:          return GLFW_GAMEPAD_AXIS_RIGHT_Y;
        case Axis::LTrigger:    return GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;
        case Axis::RTrigger:    return GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
        }
        return GLFW_KEY_UNKNOWN;
    }

    std::int32_t Joystick::convertToGLFWHat(Hat hat) noexcept
    {
        switch (hat)
        {
        case Hat::Unknown:      return GLFW_KEY_UNKNOWN;
        case Hat::Center:       return GLFW_HAT_CENTERED;
        case Hat::Up:           return GLFW_HAT_UP;
        case Hat::Right:        return GLFW_HAT_RIGHT;
        case Hat::Down:         return GLFW_HAT_DOWN;
        case Hat::Left:         return GLFW_HAT_LEFT;
        case Hat::UpRight:      return GLFW_HAT_RIGHT_UP;
        case Hat::UpLeft:       return GLFW_HAT_LEFT_UP;
        case Hat::DownRight:    return GLFW_HAT_RIGHT_DOWN;
        case Hat::DownLeft:     return GLFW_HAT_LEFT_DOWN;
        }
        return GLFW_KEY_UNKNOWN;
    }
}