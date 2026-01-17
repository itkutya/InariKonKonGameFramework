#include "InariKonKon/UI/Widgets/Widget.hpp"

#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    Widget::Widget(const UI::Data& data, const Model& model, const ShaderProgram& shader, const Texture* texture) noexcept
        : UI(data), m_model(model), m_shader(shader)
    {
        static Camera defaultUICamera{ Camera::Type::None, {}, 0.f, 0.f, -1.f, 1.f };
        this->addComponent(Drawable
            {
                this->m_model,
                this->m_shader,
                defaultUICamera,
                texture
            });
    }

    Widget::~Widget() noexcept
    {
        this->removeComponent<Drawable>();
    }

    const Model& Widget::getModel() const noexcept
    {
        return this->m_model;
    }

    const std::vector<UIVertex> Widget::getVertices() const noexcept
    {
        const auto vertexBuffer = this->m_model.getVertexBuffer<UIVertex>();
        return std::vector<UIVertex>(vertexBuffer.begin(), vertexBuffer.end());
    }

    const std::vector<std::uint32_t>& Widget::getIndices() const noexcept
    {
        return this->m_model.getIndices();
    }

    const ShaderProgram& Widget::getShaderProgram() const noexcept
    {
        return this->m_shader;
    }

    void Widget::setColor(Color color) noexcept
    {
        this->m_model.setColor<UIVertex>(color);
    }
}