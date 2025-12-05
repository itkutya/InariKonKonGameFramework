#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    const Model& UIManager::getDefaultUIModel() const noexcept
    {
        return this->m_defaultUIModel;
    }

    const Shader& UIManager::getDefaultUIVertexShader() const noexcept
    {
        return this->m_defaultUIVertexShader;
    }

    const Shader& UIManager::getDefaultUIFragmentShader() const noexcept
    {
        return this->m_defaultUIFragmentShader;
    }

    const Camera& UIManager::getDefaultUICamera() const noexcept
    {
        return this->m_defaultUICamera;
    }

    Drawable UIManager::createDefaultDrawableObject() noexcept
    {
        Drawable drawable
        {  
            this->m_defaultUIModel,
            this->m_defaultUIVertexShader,
            this->m_defaultUIFragmentShader,
            this->m_defaultUICamera
        };
        return drawable;
    }
}