#pragma once

#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    class Window;
    class Entity;

    struct Drawer final
    {
        using ComponentType = Drawable;

        void operator()(const Entity& entity, ComponentType& component, const Window& window) const noexcept;
    };
}