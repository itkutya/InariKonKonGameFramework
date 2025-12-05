#ifndef IKK_ENTITY_HPP
#define IKK_ENTITY_HPP

#include <cstdint>
#include <utility>

#include "InariKonKon/ECS/ECS.hpp"

namespace ikk
{
    class [[nodiscard]] Entity
    {
    public:
        using IDType = std::uint32_t;

        [[nodiscard]] Entity() noexcept;

        Entity(const Entity& other) noexcept;
        Entity(Entity&& other) noexcept;

        Entity& operator=(const Entity& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;

        virtual ~Entity() noexcept = default;

        [[nodiscard]] virtual const IDType& getID() const noexcept final;

        template<ComponentConcept Component>
        void addComponent(Component&& component) const noexcept;

        template<ComponentConcept Component>
        void removeComponent() const noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] bool hasComponent() const noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] std::expected<Component*, Error> getComponent() const noexcept;

        template<class System, class... Args> requires SystemConcept<System, Args...>
        void applySystem(Args&&... args) const noexcept;
    private:
        IDType m_id = 0;
    };

    template<ComponentConcept Component>
    void Entity::addComponent(Component&& component) const noexcept
    {
        ECS::addComponentToEntity<Component>(*this, std::forward<Component>(component));
    }

    template<ComponentConcept Component>
    void Entity::removeComponent() const noexcept
    {
        ECS::removeComponentFromEntity<Component>(*this);
    }

    template<ComponentConcept Component>
    bool Entity::hasComponent() const noexcept
    {
        return ECS::hasComponentInEntity<Component>(*this);
    }

    template<ComponentConcept Component>
    std::expected<Component*, Error> Entity::getComponent() const noexcept
    {
        return ECS::getComponentOfEntity<Component>(*this);
    }

    template<class System, class... Args> requires SystemConcept<System, Args...>
    void Entity::applySystem(Args&&... args) const noexcept
    {
        ECS::applySystemOnEntity<System>(*this, std::forward<Args>(args)...);
    }
}

#endif