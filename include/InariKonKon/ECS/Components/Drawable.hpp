#ifndef IKK_DRAWABLE_HPP
#define IKK_DRAWABLE_HPP

#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"
#include "InariKonKon/Shader/Shader.hpp"
#include "InariKonKon/Model/Model.hpp"

namespace ikk
{
    class [[nodiscard]] Drawable final
    {
    public:
        [[nodiscard]] Drawable(Model& model, Shader& vertex, Shader& fragment, Camera& camera) noexcept;

        Drawable(const Drawable& other) noexcept = default;
        Drawable(Drawable&& other) noexcept = default;

        Drawable& operator=(const Drawable& other) noexcept = default;
        Drawable& operator=(Drawable&& other) noexcept = default;

        ~Drawable() noexcept = default;

        void setActive(bool active = true) noexcept;

        bool isActive() const noexcept;

        const Model* getModel() const noexcept;
        const Shader* getVertexShader() const noexcept;
        const Shader* getFragmentShader() const noexcept;
        const Camera* getCamera() const noexcept;
    private:
        bool m_disabled = true;
        
        Model* m_model = nullptr;
        Shader* m_vertex = nullptr;
        Shader* m_fragment = nullptr;
        Camera* m_camera = nullptr;
    };
}

#endif