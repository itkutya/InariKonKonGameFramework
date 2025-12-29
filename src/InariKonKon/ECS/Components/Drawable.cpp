#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    Drawable::Drawable(Type type, Model& model, ShaderProgram& shaderProgram, Camera& camera) noexcept
        : m_type(type), m_model(&model), m_shaderProgram(&shaderProgram), m_camera(&camera)
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

    const Drawable::Type& Drawable::getType() const noexcept
    {
        return this->m_type;
    }

    Model* Drawable::getModel() noexcept
    {
        return this->m_model;
    }

    ShaderProgram* Drawable::getShaderProgram() noexcept
    {
        return this->m_shaderProgram;
    }

    Camera* Drawable::getCamera() noexcept
    {
        return this->m_camera;
    }

    const Model* Drawable::getModel() const noexcept
    {
        return this->m_model;
    }

    const ShaderProgram* Drawable::getShaderProgram() const noexcept
    {
        return this->m_shaderProgram;
    }

    const Camera* Drawable::getCamera() const noexcept
    {
        return this->m_camera;
    }
}