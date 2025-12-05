#include "InariKonKon/ECS/Entities/Entity.hpp"

#include "InariKonKon/Utility/IDGenerator.hpp"

namespace ikk
{
    Entity::Entity() noexcept
        : m_id(getNextAvailableIDfor<Entity>())
    {
    }

    Entity::Entity(const Entity& other) noexcept
        : m_id(getNextAvailableIDfor<Entity>())
    {
    }

    Entity::Entity(Entity&& other) noexcept
        : m_id(other.m_id)
    {
        other.m_id = 0;
    }

    Entity& Entity::operator=(const Entity& other) noexcept
    {
        if (this != &other)
            this->m_id = getNextAvailableIDfor<Entity>();
        return *this;
    }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this != &other)
        {
            this->m_id = other.m_id;
            other.m_id = 0;
        }
        return *this;
    }

    const Entity::IDType& Entity::getID() const noexcept
    {
        return this->m_id;
    }
}