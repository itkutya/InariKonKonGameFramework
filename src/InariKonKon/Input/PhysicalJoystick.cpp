#include "InariKonKon/Input/PhysicalJoystick.hpp"

#include "InariKonKon/Core/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Utility/Utility.hpp"

namespace ikk
{
    PhysicalJoystick::PhysicalJoystick(Joystick::ID id, float threshold) noexcept
        : m_id(id), m_name(glfwGetJoystickName(id)), m_threshold(threshold), m_isGamepadInputAvailable(glfwJoystickIsGamepad(id))
    {
        this->m_buttons = glfwGetJoystickButtons(this->m_id, &this->m_joystickButtonCount);
        this->m_axes = glfwGetJoystickAxes(this->m_id, &this->m_joystickAxesCount);
        this->m_hats = glfwGetJoystickHats(this->m_id, &this->m_joystickHatCount);

        if (this->m_isGamepadInputAvailable)
            this->m_name = glfwGetGamepadName(id);

        glfwSetJoystickUserPointer(this->m_id, this);
    }

    bool PhysicalJoystick::operator==(const PhysicalJoystick& other) const noexcept
    {
        return this->m_id == other.m_id;
    }

    [[nodiscard]] bool PhysicalJoystick::isConnected(Joystick::ID id) noexcept
    {
        return glfwJoystickPresent(I32(id)) == GLFW_TRUE;
    }

    std::int32_t PhysicalJoystick::getJoystickButtonState(Joystick::Button button) const noexcept
    {
        const std::int32_t index = Joystick::convertToGLFWButton(button);
        
        if (index > this->m_joystickButtonCount)
            return 0;

        if (this->m_isGamepadInputAvailable)
            if (GLFWgamepadstate state{}; glfwGetGamepadState(this->m_id, &state) != GLFW_FALSE)
                return state.buttons[index];

        return this->m_buttons[index];
    }

    float PhysicalJoystick::getJoystickAxisValue(Joystick::Axis axis) const noexcept
    {
        const std::int32_t index = Joystick::convertToGLFWAxis(axis);
        if (index > this->m_joystickAxesCount)
            return 0.f;

        if (this->m_isGamepadInputAvailable)
            if (GLFWgamepadstate state{}; glfwGetGamepadState(this->m_id, &state) != GLFW_FALSE)
                return state.axes[index];

        return this->m_axes[index];
    }

    bool PhysicalJoystick::getJoystickHatState(std::uint32_t id, Joystick::Hat hat) const noexcept
    {
        const std::int32_t index = Joystick::convertToGLFWHat(hat);
        if (index > this->m_joystickHatCount)
            return false;

        return this->m_hats[id] & index;
    }
}