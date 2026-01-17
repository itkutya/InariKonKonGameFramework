#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/Assets/Texture/Texture.hpp"

namespace ikk
{
    Drawable::Drawable(const Model& model, const ShaderProgram& shaderProgram, const Camera& camera, const Texture* texture) noexcept
        : m_model(&model), m_shaderProgram(&shaderProgram), m_camera(&camera), m_texture(texture)
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
}