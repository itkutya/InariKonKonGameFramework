#include "InariKonKon/ECS/Systems/Drawer.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Core/Window/Window.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    void Drawer::operator()(const Entity& entity, Drawable& component, const Window& window) const noexcept
    {
        if (component.isActive() == false)
        {
            DEBUG_LOG(Log::Level::Warning, "Entity's drawable component is not active.");
            return;
        }

        const ShaderProgram& shader = component.getShaderProgram();
        if (entity.hasComponent<Transform3D>() == true)
        {
            const Transform3D* transform = entity.getComponent<Transform3D>().value();
            shader.setUniform("model", transform->getWorldMatrix());
        }
        else if (entity.hasComponent<Transform2D>() == true)
        {
            const Transform2D* transform = entity.getComponent<Transform2D>().value();
            shader.setUniform("model", transform->getWorldMatrix());
        }
        else
        {
            DEBUG_LOG(Log::Level::Warning, "No Transform component found for drawable entity.");
            return;
        }
        window.getRenderer()->draw(entity);
    }
}