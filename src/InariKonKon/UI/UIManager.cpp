#include "InariKonKon/UI/UIManager.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp" // IWYU pragma: keep

#include "InariKonKon/ECS/Components/Drawable.hpp"

namespace ikk
{
    const Model& UIManager::getDefaultUIModel() const noexcept
    {
        return this->m_defaultUIModel;
    }

    const ShaderProgram& UIManager::getDefaultShaderProgram() const noexcept
    {
        return this->m_defaultUIShader;
    }

    const Camera& UIManager::getDefaultUICamera() const noexcept
    {
        return this->m_defaultUICamera;
    }

    Drawable UIManager::createDefaultDrawableObject() noexcept
    {
        static Drawable drawable
        {
            this->m_defaultUIModel,
            this->m_defaultUIShader,
            this->m_defaultUICamera
        };
        return drawable;
    }
}