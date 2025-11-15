#ifndef IKK_USER_INPUT_HPP
#define IKK_USER_INPUT_HPP

#include <unordered_map>
#include <string>
#include <variant>

#include "InariKonKon/Input/Joystick.hpp"
#include "InariKonKon/Input/Keyboard.hpp"
#include "InariKonKon/Input/Mouse.hpp"

namespace ikk
{
    struct [[nodiscard]] UserInput final
    {
        using InputType = std::variant<Keyboard::KeyCode, Keyboard::ScanCode, Mouse::Button, Mouse::Wheel, Joystick::Button, Joystick::Axis, Joystick::Hat>;
        
        std::unordered_map<std::string, InputType> keyBindings = {};
    };
}

#endif