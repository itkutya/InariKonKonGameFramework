#pragma once

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/Utility/Time.hpp"

namespace ikk
{
    class Entity;

    struct Animator final
    {
        //TODO:
        //Animation component!
        using ComponentType = Transform3D;

        void operator()(const Entity& entity, Transform3D& component, const Time& dt) const noexcept;
    };
}