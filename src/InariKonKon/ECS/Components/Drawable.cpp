#include "InariKonKon/ECS/Components/Drawable.hpp"

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

    const std::function<void(const Window& window)>& Drawable::getCallback() const noexcept
    {
        return this->m_drawCallback;
    }
}