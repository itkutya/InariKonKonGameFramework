#include "InariKonKon/UI/UIManager.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp" // IWYU pragma: keep
#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/Core/Window/Window.hpp"

namespace ikk
{
    //TODO:
    //No OpenGL calls in UIManager...
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
            &(this->m_defaultUICamera.getProjectionMatrix(window.getViewport()).convertTo<MatrixOrdering::ColumnMajor>().at(0, 0)));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}