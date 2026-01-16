#pragma once

#include <algorithm>
#include <expected>
#include <concepts>
#include <utility>
#include <vector>
#include <ranges>

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Utility/Error.hpp"

namespace ikk
{
    class Entity;

    template<class T>
    concept ComponentConcept = std::movable<T>;

    template<class System, class... Args>
    concept SystemConcept =
        requires(System system, const Entity& entity, typename System::ComponentType& component, Args&&... args)
        {
            typename System::ComponentType;
            { system(entity, component, std::forward<Args>(args)...) } noexcept;
        } && std::default_initializable<System> && ComponentConcept<typename System::ComponentType> && sizeof(System) <= 1;

    class ECS final : public NonConstructible
    {
        template<ComponentConcept Component>
        using EntityComponentPair = std::pair<const Entity*, Component>;

        template<ComponentConcept Component>
        using EntityComponentStorage = std::vector<EntityComponentPair<Component>>;

        template<ComponentConcept Component>
        [[nodiscard]] static constexpr auto matchEntity(const Entity& entity) noexcept;
    public:
        template<ComponentConcept Component>
        [[nodiscard]] static auto getComponentsView() noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] static auto getEntitiesWithComponentView() noexcept;

        template<class System, class... Args> requires SystemConcept<System, Args...>
        static void update(Args&&... args) noexcept;
    private:
        template<ComponentConcept Component>
        static void addComponentToEntity(const Entity& entity, Component&& component) noexcept;

        template<ComponentConcept Component>
        static void removeComponentFromEntity(const Entity& entity) noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] static bool hasComponentInEntity(const Entity& entity) noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] static std::expected<Component*, Error> getComponentOfEntity(const Entity& entity) noexcept;

        template<class System, class... Args> requires SystemConcept<System, Args...>
        static void applySystemOnEntity(const Entity& entity, Args&&... args) noexcept;

        template<ComponentConcept Component>
        [[nodiscard]] static EntityComponentStorage<Component>& getComponentStorage();

        friend class Entity;
    };

    template<ComponentConcept Component>
    constexpr auto ECS::matchEntity(const Entity& entity) noexcept
    {
        return [&entity](const EntityComponentPair<Component>& pair) noexcept -> bool
        {
            return pair.first == &entity;
        };
    }

    template<ComponentConcept Component>
    auto ECS::getComponentsView() noexcept
    {
        return getComponentStorage<Component>() | std::views::transform([](EntityComponentPair<Component>& pair) -> Component& { return pair.second; });
    }

    template<ComponentConcept Component>
    auto ECS::getEntitiesWithComponentView() noexcept
    {
        return getComponentStorage<Component>() | std::views::transform([](const EntityComponentPair<Component>& pair) -> const Entity* { return pair.first; });
    }

    template<class System, class... Args> requires SystemConcept<System, Args...>
    void ECS::update(Args&&... args) noexcept
    {
        using Component = typename System::ComponentType;
        EntityComponentStorage<Component>& components = getComponentStorage<Component>();
        for (const Entity* entity : getEntitiesWithComponentView<Component>())
            if (entity != nullptr)
                applySystemOnEntity<System>(*entity, std::forward<Args>(args)...);
    }

    template<ComponentConcept Component>
    void ECS::addComponentToEntity(const Entity& entity, Component&& component) noexcept
    {
        EntityComponentStorage<Component>& components = getComponentStorage<Component>();
        if (std::ranges::find_if(components, matchEntity<Component>(entity)) == components.end())
            components.emplace_back(&entity, std::move(component));
    }

    template<ComponentConcept Component>
    void ECS::removeComponentFromEntity(const Entity& entity) noexcept
    {
        std::erase_if(getComponentStorage<Component>(), matchEntity<Component>(entity));
    }

    template<ComponentConcept Component>
    bool ECS::hasComponentInEntity(const Entity& entity) noexcept
    {
        EntityComponentStorage<Component>& components = getComponentStorage<Component>();
        return std::ranges::find_if(components, matchEntity<Component>(entity)) != components.end();
    }

    template<ComponentConcept Component>
    std::expected<Component*, Error> ECS::getComponentOfEntity(const Entity& entity) noexcept
    {
        EntityComponentStorage<Component>& components = getComponentStorage<Component>();
        if (auto it = std::ranges::find_if(components, matchEntity<Component>(entity)); it != components.end())
            return std::expected<Component*, Error>{ &it->second };
        else
            return std::unexpected(Error{ "Entity does not have the requested component." });
    }

    template<class System, class... Args> requires SystemConcept<System, Args...>
    void ECS::applySystemOnEntity(const Entity& entity, Args&&... args) noexcept
    {
        using Component = typename System::ComponentType;
        EntityComponentStorage<Component>& components = getComponentStorage<Component>();
        if (auto it = std::ranges::find_if(components, matchEntity<Component>(entity)); it != components.end())
            System{}(*it->first, it->second, std::forward<Args>(args)...);
    }

    template<ComponentConcept Component>
    ECS::EntityComponentStorage<Component>& ECS::getComponentStorage()
    {
        static EntityComponentStorage<Component> instance{};
        return instance;
    }
}