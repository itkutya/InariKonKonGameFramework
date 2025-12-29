#include "InariKonKon/Input/Input.hpp"

#include "InariKonKon/Core/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep

namespace ikk
{
    Input::State Input::convertFromGLFWAction(std::int32_t action) noexcept
    {
        switch (action)
        {
            case GLFW_PRESS:        return State::Pressed;
            case GLFW_RELEASE:      return State::Released;
            case GLFW_REPEAT:       return State::Repeat;
        }
        return State::Unknown;
    }

    std::int32_t Input::convertToGLFWAction(State type) noexcept
    {
        switch (type)
        {
            case State::Unknown:    return GLFW_KEY_UNKNOWN;
            case State::Pressed:    return GLFW_PRESS;
            case State::Released:   return GLFW_RELEASE;
            case State::Repeat:     return GLFW_REPEAT;
        }
        return GLFW_KEY_UNKNOWN;
    }
}