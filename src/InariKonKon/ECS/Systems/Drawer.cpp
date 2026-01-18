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

        using Transform = std::variant<const Transform3D*, const Transform2D*>;
        const std::expected<Transform, Error> transform = entity.getComponent<Transform3D>().transform(
            [](const Transform3D* t) noexcept -> Transform
            {
                return t;
            }).or_else([&](const Error&) noexcept
            {
                return entity.getComponent<Transform2D>().transform([](const Transform2D* t) noexcept -> Transform
                {
                    return t;
                });
            });
        
        if (transform.has_value() == false)
        {
            DEBUG_LOG(Log::Level::Warning, "No Transform component found for drawable entity.");
            return;
        }

        std::visit([&component](const auto* transform)
            {
                const ShaderProgram& shader = component.getShaderProgram();
                shader.setUniform("model", transform->getWorldMatrix());
            }, transform.value());

        window.getRenderer()->draw(entity);

        //TODO:
        //Better solution...
        if (component.getCallback())
            component.getCallback()(window);
    }
}