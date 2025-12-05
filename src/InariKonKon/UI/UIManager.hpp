#ifndef IKK_UI_MANAGER_HPP
#define IKK_UI_MANAGER_HPP

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/Utility/Singleton.hpp"

namespace ikk
{
    class [[nodiscard]] UIManager final : public Singleton<UIManager>
    {
    public:
        ~UIManager() noexcept = default;

        [[nodiscard]] const Model& getDefaultUIModel() const noexcept;
        [[nodiscard]] const Shader& getDefaultUIVertexShader() const noexcept;
        [[nodiscard]] const Shader& getDefaultUIFragmentShader() const noexcept;
        [[nodiscard]] const Camera& getDefaultUICamera() const noexcept;

        [[nodiscard]] Drawable createDefaultDrawableObject() noexcept;
    private:
        Model m_defaultUIModel = {};
        Shader m_defaultUIVertexShader = { Shader::Type::Vertex, "" };
        Shader m_defaultUIFragmentShader = { Shader::Type::Fragment, "" };
        Camera m_defaultUICamera = {};

        friend Singleton<UIManager>;
    };
}

#endif