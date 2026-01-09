#include "InariKonKon/ECS/Systems/Updater.hpp"

namespace ikk
{
    void Updater::operator()(const Entity& entity, ComponentType& component) const noexcept
    {
        component.update();
    }
}