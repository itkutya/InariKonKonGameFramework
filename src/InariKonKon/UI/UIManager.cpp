#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    const ShaderProgram& UIManager::getDefaultShaderProgram() const noexcept
    {
        return this->m_defaultUIShader;
    }

    const Camera& UIManager::getDefaultUICamera() const noexcept
    {
        return this->m_defaultUICamera;
    }
}