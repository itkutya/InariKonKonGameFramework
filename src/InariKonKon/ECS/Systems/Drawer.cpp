#include "InariKonKon/ECS/Systems/Drawer.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    void Drawer::operator()(const Entity& entity, Drawable& component, const Window& window) const noexcept
    {
        if (component.isActive() == false)
            return;

        const std::expected<Transform3D*, Error> transform = entity.getComponent<Transform3D>(); 
        if (transform.has_value() == false)
        {
            DEBUG_LOG(Log::Level::Warning, "Transform component not found for drawable entity.");
            return;
        }

        window.getRenderer()->draw(entity, component, *transform.value());
    }
}