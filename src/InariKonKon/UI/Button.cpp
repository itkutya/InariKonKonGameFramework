#include "InariKonKon/UI/Button.hpp"

//#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    Button::Button(Vec2f position, Vec2f size, RotationDegf rotation, Color color, float radius) noexcept
        : UI(position, size, rotation)
    {
        //Model is a rectangle, shader is a basic UI shader, camera is an orthographic camera
        //this->addComponent(Drawable{});
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