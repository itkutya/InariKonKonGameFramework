#include "InariKonKon/Input/InputManager.hpp"

#include <ranges> // IWYU pragma: keep

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Input/Joystick.hpp"
#include "InariKonKon/Input/PhysicalJoystick.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
    void InputManager::checkForConnectedJoysticks() noexcept
    {
        for (Joystick::ID id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_16; ++id)
            if (PhysicalJoystick::isConnected(id) == true)
                this->addJoystick(id);
    }

    const auto InputManager::findJoystick(Joystick::ID id) const noexcept
    {
        return std::ranges::find(this->m_connectedJoysticks, id);
    }

    void InputManager::addJoystick(Joystick::ID id) noexcept
    {
        if (const auto found = this->findJoystick(id); found == this->m_connectedJoysticks.end())
            this->m_connectedJoysticks.emplace_back(PhysicalJoystick{ id });
    }

    void InputManager::removeJoystick(Joystick::ID id) noexcept
    {
        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            this->m_connectedJoysticks.erase(found);
    }

    Input::State InputManager::getKeyboardButtonState(const Window& window, Keyboard::KeyCode keycode) const noexcept
    {
        return Input::convertFromGLFWAction(glfwGetKey(window.m_window, Keyboard::convertToGLFWKeyCode(keycode)));
    }

    Input::State InputManager::getKeyboardButtonState(const Window& window, Keyboard::ScanCode scancode) const noexcept
    {
        return getKeyboardButtonState(window, Keyboard::convertToKeyCode(scancode));
    }

    Input::State InputManager::getMouseButtonState(const Window& window, Mouse::Button button) const noexcept
    {
        return Input::convertFromGLFWAction(glfwGetMouseButton(window.m_window, Mouse::convertToGLFWButton(button)));
    }
    
    Input::State InputManager::getJoystickButtonState(Joystick::ID id, Joystick::Button button) const noexcept
    {
        if (PhysicalJoystick::isConnected(id) == false)
            return Input::State::Unknown;

        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            return Input::convertFromGLFWAction(found->getJoystickButtonState(button));
        else
            return Input::State::Unknown;
    }

    float InputManager::getJoystickAxisValue(Joystick::ID id, Joystick::Axis axis) const noexcept
    {
        if (PhysicalJoystick::isConnected(id) == false)
            return 0.f;

        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            return found->getJoystickAxisValue(axis);
        else
            return 0.f;
    }
    
    bool InputManager::getJoystickAxisState(Joystick::ID id, Joystick::Axis axis) const noexcept
    {
        if (PhysicalJoystick::isConnected(id) == false)
            return false;

        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            return found->getJoystickAxisValue(axis) > found->m_threshold;
        else
            return false;
    }
    
    bool InputManager::getJoystickHatState(Joystick::ID id, std::size_t hat_id, Joystick::Hat hat) const noexcept
    {
        if (PhysicalJoystick::isConnected(id) == false)
            return false;

        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            return found->getJoystickHatState(hat_id, hat);
        else
            return false;
    }
}