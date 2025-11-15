#include "InariKonKon/UI/Button.hpp"

//#include "InariKonKon/ECS/Components/Transform.hpp"
//#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    Button::Button(const Window& window) noexcept
    {
        //this->addComponent(UI{}); --> This should hold all of the below ones...
        //this->addComponent(Transform2D{});
        //this->addComponent(Drawable{});
        //this->addComponent(UserInput{});
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