#pragma once

#include "InariKonKon/ECS/Components/Updateable.hpp"

namespace ikk
{
    class Entity;

    struct Updater final
    {
        using ComponentType = Updateable;

        void operator()(const Entity& entity, ComponentType& component) const noexcept;
    };
}