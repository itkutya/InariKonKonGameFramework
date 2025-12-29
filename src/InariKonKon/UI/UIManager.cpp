#include "InariKonKon/UI/UIManager.hpp"

#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"
#include "InariKonKon/Core/Window/Window.hpp"
#include "InariKonKon/Math/Mat.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp" // IWYU pragma: keep

namespace ikk
{
    UIManager::UIManager() noexcept
    {
        glGenBuffers(1, &this->m_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, this->m_ubo);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4x4f), NULL, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glUniformBlockBinding(this->m_defaultUIShader.getID(),
            glGetUniformBlockIndex(this->m_defaultUIShader.getID(), "Matrices"), 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, this->m_ubo);
    }

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
            Drawable::Type::UI,
            this->m_defaultUIModel,
            this->m_defaultUIShader,
            this->m_defaultUICamera
        };
        return drawable;
    }

    void UIManager::updateUniformBufferObjects(const Window& window) noexcept
    {
        glBindBuffer(GL_UNIFORM_BUFFER, this->m_ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4x4f),
            &this->m_defaultUICamera.getProjectionMatrix(window.getViewport()).at(0, 0)); 
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}