#include "InariKonKon/UI/Widgets/Button.hpp"

#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Button::Button(Vec2f position, Vec2f size, RotationDegf rotation, Color color, float radius) noexcept
        : UI(position, size, rotation)
    {
        this->addComponent(UIManager::getInstance().createDefaultDrawableObject());

        for (Vertex& vertex : this->getComponent<Drawable>().value()->getModel()->m_vertices)
            vertex.color = color;
    }

    const Button::State& Button::getState() const noexcept
    {
        return this->m_state;
    }

    bool Button::isPressed() const noexcept
    {
        return this->m_state != State::None;
    }
}