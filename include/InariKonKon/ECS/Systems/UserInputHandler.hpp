#ifndef IKK_USER_INPUT_HANDLER_HPP
#define IKK_USER_INPUT_HANDLER_HPP

#include "InariKonKon/ECS/Components/UserInput.hpp"

namespace ikk
{
    class Entity;

    struct UserInputHandler final
    {
        using ComponentType = UserInput;

        void operator()(const Entity& entity, UserInput& component) const noexcept;
    };
}

#endif