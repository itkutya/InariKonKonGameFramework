#ifndef IKK_TRANSFORMER_HPP
#define IKK_TRANSFORMER_HPP

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/Utility/Time.hpp"

namespace ikk
{
    class Entity;

    struct Transformer final
    {
        using ComponentType = Transform3D;

        void operator()(const Entity& entity, Transform3D& component, const Time& dt) const noexcept;
    };
}

#endif