#include "InariKonKon/ECS/Entities/Entity.hpp"

namespace ikk
{
    Entity::Entity(Entity::IDType id) noexcept
        : m_id(id)
    {
    }

    const Entity::IDType& Entity::getID() const noexcept
    {
        return this->m_id;
    }

    const Entity::IDType Entity::getNextEntityID() noexcept
    {
        static Entity::IDType ID = 0;
        return ++ID;
    }
}