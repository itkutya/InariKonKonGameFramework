#ifndef IKK_INPUT_MANAGER_HPP
#define IKK_INPUT_MANAGER_HPP

#include <vector>

#include "InariKonKon/Utility/Singleton.hpp"

#include "InariKonKon/Input/Keyboard.hpp"
#include "InariKonKon/Input/Joystick.hpp"
#include "InariKonKon/Input/Mouse.hpp"

#include "InariKonKon/Input/PhysicalJoystick.hpp"

#include "InariKonKon/Input/Input.hpp"

//TODO:
//Serialized input handleing
//conversion between Input <--> std::string_view (easy access)

namespace ikk
{
    class InputManager final : public Singleton<InputManager>
    {
        InputManager() noexcept = default;
    public:
        ~InputManager() noexcept = default;

        void addJoystick(Joystick::ID id) noexcept;
        void removeJoystick(Joystick::ID id) noexcept;

        [[nodiscard]] Input::State getKeyboardButtonState(const Window& window, Keyboard::KeyCode keycode) const noexcept;
        [[nodiscard]] Input::State getKeyboardButtonState(const Window& window, Keyboard::ScanCode scancode) const noexcept;

        [[nodiscard]] Input::State getMouseButtonState(const Window& window, Mouse::Button button) const noexcept;
        
        [[nodiscard]] Input::State getJoystickButtonState(Joystick::ID id, Joystick::Button button) const noexcept;
        [[nodiscard]] float getJoystickAxisValue(Joystick::ID id, Joystick::Axis axis) const noexcept;
        [[nodiscard]] bool getJoystickAxisState(Joystick::ID id, Joystick::Axis axis) const noexcept;
        [[nodiscard]] bool getJoystickHatState(Joystick::ID id, std::size_t hat_id, Joystick::Hat hat) const noexcept;
    private:
        std::vector<PhysicalJoystick> m_connectedJoysticks;

        void checkForConnectedJoysticks() noexcept;

        [[nodiscard]] const auto findJoystick(Joystick::ID id) const noexcept;

        friend Singleton<InputManager>;
        friend class Window;
    };
}

#endif