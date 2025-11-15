#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    Drawable::Drawable(Model& model, Shader& vertex, Shader& fragment, Camera& camera) noexcept
        : m_model(&model), m_vertex(&vertex), m_fragment(&fragment), m_camera(&camera)
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

    const Model* Drawable::getModel() const noexcept
    {
        return this->m_model;
    }

    const Shader* Drawable::getVertexShader() const noexcept
    {
        return this->m_vertex;
    }

    const Shader* Drawable::getFragmentShader() const noexcept
    {
        return this->m_fragment;
    }

    const Camera* Drawable::getCamera() const noexcept
    {
        return this->m_camera;
    }
}