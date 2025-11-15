#ifndef IKK_PHYSICAL_JOYSTICK_HPP
#define IKK_PHYSICAL_JOYSTICK_HPP

#include <string_view>
#include <cstdint>

#include "InariKonKon/Input/Joystick.hpp"

namespace ikk
{
    class [[nodiscard]] PhysicalJoystick final
    {
    public:
        //TODO:
        //Make it fool proof...
        PhysicalJoystick(Joystick::ID id, float threshold = 0.1f) noexcept;

        ~PhysicalJoystick() noexcept = default;

        PhysicalJoystick(const PhysicalJoystick&) noexcept = default;
        PhysicalJoystick(PhysicalJoystick&&) noexcept = default;

        PhysicalJoystick& operator=(const PhysicalJoystick&) noexcept = default;
        PhysicalJoystick& operator=(PhysicalJoystick&&) noexcept = default;

        [[nodiscard]] bool operator==(const PhysicalJoystick& other) const noexcept;

        [[nodiscard]] static bool isConnected(Joystick::ID id) noexcept;

        [[nodiscard]] std::int32_t getJoystickButtonState(Joystick::Button button) const noexcept;
        [[nodiscard]] float getJoystickAxisValue(Joystick::Axis axis) const noexcept;
        [[nodiscard]] bool getJoystickHatState(std::uint32_t id, Joystick::Hat hat) const noexcept;
    private:
        Joystick::ID m_id;

        std::string_view m_name = {};

        std::int32_t m_joystickAxesCount = 0;
        std::int32_t m_joystickButtonCount = 0;
        std::int32_t m_joystickHatCount = 0;

        float m_threshold = 0.1f;

        bool m_isGamepadInputAvailable = false;

        const std::uint8_t* m_buttons = nullptr;
        const float* m_axes = nullptr;
        const std::uint8_t* m_hats = nullptr;

        friend class InputManager;
    };
}

#endif