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

        Model m_defaultUIModel =
        {
        .m_vertices =
            {
                {{-1.f,  1.f, -1.f}}, {{ 1.f,  1.f, -1.f}},
                {{ 1.f, -1.f, -1.f}}, {{-1.f, -1.f, -1.f}}
            },
        .m_indices =
            {
                0, 1, 2,
                2, 3, 0
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

                uniform mat3 model;

                layout (std140, binding = 0) uniform Matrices
                {
                    mat4 projection;
                };

                out vec4 fragColor;

                void main()
                {
                    gl_Position = transpose(projection) * vec4(model * position, 1.0f);
                    fragColor = color;
                }
                )"
            },
            FragmentShader
            {
                R"(
                #version 460 core

                in vec4 fragColor;

                out vec4 color;

                void main()
                {
                    color = fragColor;
                }
                )"
            }
        };

        Camera m_defaultUICamera = {};

        friend Singleton<UIManager>;
    };
}

#endif