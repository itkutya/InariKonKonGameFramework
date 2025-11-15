#include "InariKonKon/Input/Mouse.hpp"

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
    Vec2d Mouse::getCursorPosition(const Window& window) noexcept
    {
        double xpos = 0.0, ypos = 0.0;
        glfwGetCursorPos(window.m_window, &xpos, &ypos);
        return Vec2d{ xpos, ypos };
    }

    std::int32_t Mouse::convertToGLFWButton(Button button) noexcept
    {
        switch (button)
        {
            case Button::Unknown:   return GLFW_KEY_UNKNOWN;
            case Button::Left:      return GLFW_MOUSE_BUTTON_LEFT;
            case Button::Right:     return GLFW_MOUSE_BUTTON_RIGHT;
            case Button::Middle:    return GLFW_MOUSE_BUTTON_MIDDLE;
            case Button::Extra1:    return GLFW_MOUSE_BUTTON_4;
            case Button::Extra2:    return GLFW_MOUSE_BUTTON_5;
            case Button::Extra3:    return GLFW_MOUSE_BUTTON_6;
            case Button::Extra4:    return GLFW_MOUSE_BUTTON_7;
            case Button::Extra5:    return GLFW_MOUSE_BUTTON_8;
        }
        return GLFW_KEY_UNKNOWN;
    }

    Mouse::Button Mouse::convertFromGLFWButton(std::int32_t button) noexcept
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:    return Button::Left;
            case GLFW_MOUSE_BUTTON_RIGHT:   return Button::Right;
            case GLFW_MOUSE_BUTTON_MIDDLE:  return Button::Middle;
            case GLFW_MOUSE_BUTTON_4:       return Button::Extra1;
            case GLFW_MOUSE_BUTTON_5:       return Button::Extra2;
            case GLFW_MOUSE_BUTTON_6:       return Button::Extra3;
            case GLFW_MOUSE_BUTTON_7:       return Button::Extra4;
            case GLFW_MOUSE_BUTTON_8:       return Button::Extra5;
        }
        return Button::Unknown;
    }
}