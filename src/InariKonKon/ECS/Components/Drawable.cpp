#include "InariKonKon/ECS/Components/Drawable.hpp"

#include "InariKonKon/Core/Window/Window.hpp"

namespace ikk
{
    Drawable::Drawable(const Model& model, const ShaderProgram& shaderProgram, const Camera& camera, const Texture* texture, std::function<void(const Window& window)> drawCallback) noexcept
        : m_model(&model), m_shaderProgram(&shaderProgram), m_camera(&camera), m_texture(texture), m_drawCallback(drawCallback)
    {
    }

    void Drawable::setActive(bool active) noexcept
    {
        this->m_disabled = !active;
    }

    bool Drawable::isActive() const noexcept
    {
        return !this->m_disabled;
    }

    const Model& Drawable::getModel() const noexcept
    {
        return *this->m_model;
    }

    const ShaderProgram& Drawable::getShaderProgram() const noexcept
    {
        return *this->m_shaderProgram;
    }

    const Camera& Drawable::getCamera() const noexcept
    {
        return *this->m_camera;
    }

    const Texture* Drawable::getTexture() const noexcept
    {
        return this->m_texture;
    }

    void Drawable::draw(const Window& window) const noexcept
    {
        window.getRenderer()->draw(*this);

        if (this->m_drawCallback)
            this->m_drawCallback(window);
    }
}