#pragma once

#include <string_view>
#include <cstdint>

#include "InariKonKon/Utility/NonConstructible.hpp"

namespace ikk
{
    class Input final : public NonConstructible
    {
    public:
        enum struct State : std::int8_t
        {
            Unknown = 0,
            Pressed,
            Released,
            Repeat
        };

        [[nodiscard]] static constexpr std::string_view convertToString(State type) noexcept;
    private:
        [[nodiscard]] static State convertFromGLFWAction(std::int32_t action) noexcept;
        [[nodiscard]] static std::int32_t convertToGLFWAction(State type) noexcept;

        friend class InputManager;
        friend class EventCallbackFuncs;
    };

    constexpr std::string_view Input::convertToString(State type) noexcept
    {
        switch (type)
        {
            case State::Unknown:    return "Unknown";
            case State::Pressed:    return "Press";
            case State::Released:   return "Release";
            case State::Repeat:     return "Repeat";
        }
        return "Unknown";
    }
}