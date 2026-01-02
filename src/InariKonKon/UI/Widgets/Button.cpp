#include "InariKonKon/UI/Widgets/Button.hpp"

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Button::Button(std::string_view text, Vec2f position, Vec2f size, Degreef rotation, Color color, float radius) noexcept
        : UI(position, size, rotation), m_text(text)
    {
        for (UIVertex& vertex : this->m_model.getVertexBuffer<UIVertex>())
            vertex.color = color;

        Drawable drawable
            {
                this->getModel(),
                UIManager::getInstance().getDefaultShaderProgram(),
                UIManager::getInstance().getDefaultUICamera()
            };
        this->addComponent(std::move(drawable));
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