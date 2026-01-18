#pragma once

#include <functional>

#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"
#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"
#include "InariKonKon/Assets/Texture/Texture.hpp"
#include "InariKonKon/Assets/Model/Model.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] Drawable final
    {
    public:
        //TODO:
        //Type

        [[nodiscard]] Drawable(const Model& model, const ShaderProgram& shaderProgram, const Camera& camera,
            const Texture* texture = nullptr, std::function<void(const Window& window)> drawCallback = {}) noexcept;

        Drawable(const Drawable& other) noexcept = default;
        Drawable(Drawable&& other) noexcept = default;

        Drawable& operator=(const Drawable& other) noexcept = default;
        Drawable& operator=(Drawable&& other) noexcept = default;

        ~Drawable() noexcept = default;

        void setActive(bool active = true) noexcept;

        bool isActive() const noexcept;

        const Model& getModel() const noexcept;
        const ShaderProgram& getShaderProgram() const noexcept;
        const Camera& getCamera() const noexcept;

        const Texture* getTexture() const noexcept;
        const std::function<void(const Window& window)>& getCallback() const noexcept;
    private:
        bool m_disabled = true;
        
        const ShaderProgram* m_shaderProgram = nullptr;
        const Camera* m_camera = nullptr;
        const Model* m_model = nullptr;
        const Texture* m_texture = nullptr;

        std::function<void(const Window& window)> m_drawCallback;
    };
}