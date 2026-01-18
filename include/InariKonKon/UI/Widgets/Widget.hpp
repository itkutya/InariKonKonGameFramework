#pragma once

#include <functional>

#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"
#include "InariKonKon/Assets/Texture/Texture.hpp"
#include "InariKonKon/Assets/Model/Model.hpp"
#include "InariKonKon/UI/UI.hpp"

        //TODO:
        /*
        enum struct Pivot :std::uint8_t
        {
            TopLeft, TopCenter, TopRight,
            CenterLeft, Center, CenterRight,
            BottomLeft, BottomCenter, BottomRight
        };
        */

namespace ikk
{
    class Window;

    class [[nodiscard]] Widget : public UI
    {
    public:
        virtual ~Widget() noexcept;

        [[nodiscard]] virtual const Model& getModel() const noexcept final;
        [[nodiscard]] virtual const std::vector<UIVertex> getVertices() const noexcept final;
        [[nodiscard]] virtual const std::vector<std::uint32_t>& getIndices() const noexcept final;

        [[nodiscard]] virtual const ShaderProgram& getShaderProgram() const noexcept final;

        virtual void setColor(Color color) noexcept final;
        //TODO:
        //Rest...
    protected:
        [[nodiscard]] Widget(const UI::Data& data, const Model& model, const ShaderProgram& shader, const Texture* texture = nullptr, std::function<void(const Window& window)> drawCallback = {}) noexcept;

        Widget(const Widget&) noexcept = default;
        Widget(Widget&&) noexcept = default;

        Widget& operator=(const Widget&) noexcept = default;
        Widget& operator=(Widget&&) noexcept = default;
    private:
        Model m_model;
        ShaderProgram m_shader;
    };
}