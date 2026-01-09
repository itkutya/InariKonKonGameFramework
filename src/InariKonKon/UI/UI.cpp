#include "InariKonKon/UI/UI.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"

namespace ikk
{
    UI::UI(Vec2f position, Vec2f size, Degreef rotation) noexcept
    {
        this->addComponent(Transform2D{ position, {0.f, 0.f, rotation}, size });
    }

    UI::~UI() noexcept
    {
        this->removeComponent<Transform2D>();
    }

    void UI::setColor(const Color& color) noexcept
    {
        this->m_model.setColor<UIVertex>(color);
    }

    const Model& UI::getModel() const noexcept
    {
        return this->m_model;
    }
}