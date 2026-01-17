#pragma once

#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"
#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"
#include "InariKonKon/Utility/Singleton.hpp"

namespace ikk
{
    class Window;

    class [[nodiscard]] UIManager final : public Singleton<UIManager>
    {
    public:
        ~UIManager() noexcept = default;

        [[nodiscard]] const ShaderProgram& getDefaultShaderProgram() const noexcept;
        [[nodiscard]] const Camera& getDefaultUICamera() const noexcept;
    private:
        /*
        enum struct Pivot :std::uint8_t
        {
            TopLeft, TopCenter, TopRight,
            CenterLeft, Center, CenterRight,
            BottomLeft, BottomCenter, BottomRight
        };
        */
        const ShaderProgram m_defaultUIShader =
            {
                VertexShader
                {
                    R"(
                    #version 460 core
                    layout(location = 0) in vec3 position;
                    layout(location = 1) in vec4 color;
                    layout(location = 2) in vec2 texCoord;

                    out vec4 fragColor;
                    out vec2 fragTexCoord;

                    uniform mat3 model;

                    layout (std140, binding = 0) uniform CameraMatrices
                    {
                        mat4 projection;
                        mat4 view;
                    };

                    void main()
                    {
                        mat4 model3D = mat4(
                            vec4(model[0][0], model[0][1], 0.0, 0.0),
                            vec4(model[1][0], model[1][1], 0.0, 0.0),
                            vec4(0.0        , 0.0        , 1.0, 0.0),
                            vec4(model[2][0], model[2][1], 0.0, 1.0));
                        gl_Position = projection * view * model3D * vec4(position, 1.0);

                        fragColor = color;
                        fragTexCoord = texCoord;
                    }
                    )"
                },
                FragmentShader
                {
                    R"(
                    #version 460 core

                    in vec4 fragColor;
                    in vec2 fragTexCoord;

                    out vec4 color;

                    uniform sampler2D fontAtlas;

                    void main()
                    {
                        float alpha = texture(fontAtlas, fragTexCoord).r;
                        if (alpha != 1.0)
                            discard;

                        color = vec4(fragColor.rgb, alpha);
                    }
                    )"
                }
        };

        const Camera m_defaultUICamera = { Camera::Type::None, {}, 0.f, 0.f, -1.f, 1.f };

        friend Singleton<UIManager>;
    };
}