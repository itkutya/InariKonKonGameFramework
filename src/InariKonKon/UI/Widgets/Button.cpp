#include "InariKonKon/UI/Widgets/Button.hpp"

#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Button::Button(std::string_view text, Vec2f position, Vec2f size, Degreef rotation, Color color, float radius) noexcept
        : UI(position, size, rotation), m_text(text)
    {
        this->addComponent(UIManager::getInstance().createDefaultDrawableObject());

        for (UIVertex& vertex : this->getComponent<Drawable>().value()->getModel().getVertexBuffer<UIVertex>())
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