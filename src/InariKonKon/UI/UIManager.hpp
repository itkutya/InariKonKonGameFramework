#ifndef IKK_UI_MANAGER_HPP
#define IKK_UI_MANAGER_HPP

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/Utility/Singleton.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] UIManager final : public Singleton<UIManager>
    {
    public:
        ~UIManager() noexcept = default;

        [[nodiscard]] const Model& getDefaultUIModel() const noexcept;
        [[nodiscard]] const ShaderProgram& getDefaultShaderProgram() const noexcept;
        [[nodiscard]] const Camera& getDefaultUICamera() const noexcept;

        [[nodiscard]] Drawable createDefaultDrawableObject() noexcept;

        void updateUniformBufferObjects(const Window& window) noexcept;
    protected:
        [[nodiscard]] UIManager() noexcept;
    private:
        std::uint32_t m_ubo;

        /*
        enum struct Pivot :std::uint8_t
        {
            TopLeft, TopCenter, TopRight,
            CenterLeft, Center, CenterRight,
            BottomLeft, BottomCenter, BottomRight
        };
        */

        Model m_defaultUIModel =
            {
            std::vector<UIVertex>
                {
                    {{0.f, 0.f }}, {{0.f, 1.f }},
                    {{1.f, 0.f }}, {{1.f, 1.f }}
                },
            std::vector<std::uint32_t>
                {
                    0, 1, 2,
                    2, 1, 3
                }
            };

        ShaderProgram m_defaultUIShader =
            {
                VertexShader
                {
                    R"(
                    #version 460 core
                    layout(location = 0) in vec3 position;
                    layout(location = 1) in vec4 color;
                    layout(location = 2) in vec2 texCoord;

                    uniform mat3 model;

                    layout (std140, binding = 0) uniform Matrices
                    {
                        mat4 projection;
                    };

                    out vec4 fragColor;
                    out vec2 fragPosWorld;

                    void main()
                    {
                        mat4 model3D = mat4(
                            vec4(model[0][0], model[0][1], 0.0, 0.0),
                            vec4(model[1][0], model[1][1], 0.0, 0.0),
                            vec4(0.0        , 0.0        , 1.0, 0.0),
                            vec4(model[2][0], model[2][1], 0.0, 1.0));
                        gl_Position = projection * model3D * vec4(position, 1.0);

                        fragColor = color;
                        fragPosWorld = (model * vec3(position.xy, 1.0)).xy;
                    }
                    )"
                },
                FragmentShader
                {
                    R"(
                    #version 460 core

                    uniform mat3 model;

                    in vec4 fragColor;
                    in vec2 fragPosWorld;

                    out vec4 color;

                    void main()
                    {
                        //Goes from 0.0 to 0.5
                        float radius = 0.3; // TODO: Pass as uniform

                        vec2 fragPos = (inverse(model) * vec3(fragPosWorld, 1.0)).xy;

                        vec2 inner = clamp(fragPos, vec2(radius), vec2(1.0) - vec2(radius));
                        float dist = length(fragPos - inner);
                        float alpha = 1.0 - smoothstep(radius - 0.01, radius + 0.01, dist);

                        color = vec4(fragColor.rgb, fragColor.a * alpha);
                    }
                    )"
                }
        };

        Camera m_defaultUICamera = { Camera::Type::None, {}, 0.f, 0.f, -1.f, 1.f };

        friend Singleton<UIManager>;
    };
}

#endif