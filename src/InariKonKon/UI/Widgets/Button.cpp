#include "InariKonKon/UI/Widgets/Button.hpp"

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/ECS/Components/Updateable.hpp"
#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Button::Button(std::string_view text, Vec2f position, Vec2f size, Degreef rotation, Color color, float radius) noexcept
        : UI(position, size, rotation), m_text(text)
    {
        this->setColor(color);

        Drawable drawable
            {
                this->getModel(),
                UIManager::getInstance().getDefaultShaderProgram(),
                UIManager::getInstance().getDefaultUICamera()
            };

        this->addComponent(std::move(drawable));

        auto lambda = [this]() noexcept
            {
                if (this->getState() == Button::State::Pressed && this->m_prevState == Button::State::Pressed)
                    this->m_state = Button::State::None;

                this->m_prevState = this->getState();
            };
        
        Updateable update{lambda};
        this->addComponent(std::move(update));
    }

    const Button::State& Button::getState() const noexcept
    {
        return this->m_state;
    }

    bool Button::isPressed() const noexcept
    {
        return this->m_state != State::None;
    }

    void Button::onNotify(const MouseEvent::Button& event) noexcept
    {
        if (event.button != Mouse::Button::Left)
            return;

        switch (event.state)
        {
            case Input::State::Pressed:
                if (this->m_hovered == true)
                    this->m_state = State::Held;
                break;
            case Input::State::Released:
                if (this->m_hovered == true)
                        this->m_state = State::Pressed;
                else
                    this->m_state = State::None;
                break;
            case Input::State::Repeat:
            //Mouse can't be repeated, because GLFW does not support it sadly...
                return;
            case Input::State::Unknown:
                return;
        }
    }
    
    void Button::onNotify(const MouseEvent::Move& event) noexcept
    {
        const Transform2D& transform = *this->getComponent<Transform2D>().value();
        Rectf rect{ transform.getWorldPosition(), transform.getWorldScale() };
        this->m_hovered = rect.contains(event.position, transform.getWorldRotation());

        if (this->m_hovered == false && this->m_state == State::Held)
            this->m_state = State::Withheld;
        else if (this->m_hovered == true && this->m_state == State::Withheld)
            this->m_state = State::Held;
    }
}