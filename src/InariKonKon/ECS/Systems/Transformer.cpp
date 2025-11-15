#include "InariKonKon/ECS/Systems/Transformer.hpp"

//#include "fmt/format.h"

#include "InariKonKon/ECS/Entities/Entity.hpp"
//#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    void Transformer::operator()(const Entity& entity, Transform3D& component, const Time& dt) const noexcept
    {
        //TODO:
        //Interpolate between current and target
        //For now, just set current to target
        //component.m_current = component.m_target;
    }
}