#include "InariKonKon/UI/Button.hpp"

#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Button::Button(Vec2f position, Vec2f size, RotationDegf rotation, Color color, float radius) noexcept
        : UI(position, size, rotation)
    {
        this->addComponent(UIManager::getInstance().createDefaultDrawableObject());
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