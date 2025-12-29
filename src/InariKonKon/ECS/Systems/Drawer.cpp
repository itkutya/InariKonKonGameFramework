#include "InariKonKon/ECS/Systems/Drawer.hpp"

#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"
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

        const ShaderProgram* shader = component.getShaderProgram();

        if (entity.hasComponent<Transform3D>() == true)
        {
            const Transform3D* transform = entity.getComponent<Transform3D>().value();
            shader->setUniform("model", transform->getWorldMatrix());
        }
        else if (entity.hasComponent<Transform2D>() == true)
        {
            const Transform2D* transform = entity.getComponent<Transform2D>().value();
            shader->setUniform("model", transform->getWorldMatrix());
        }
        else
        {
            DEBUG_LOG(Log::Level::Warning, "No Transform component found for drawable entity.");
            return;
        }

        const Camera* camera = component.getCamera();

        switch (component.getType() )
        {
            case Drawable::Type::Object:
                shader->setUniform("view", camera->getViewMatrix());
                shader->setUniform("projection", camera->getProjectionMatrix(window.getAscpectRation()));
                break;
            case Drawable::Type::UI:
                shader->setUniform("projection", camera->getProjectionMatrix(window.getViewport()));
                break;
        
        }

        window.getRenderer()->draw(entity, component);
    }
}