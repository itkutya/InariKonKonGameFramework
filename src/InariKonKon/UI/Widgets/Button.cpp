#include "InariKonKon/UI/Widgets/Button.hpp"

#include "InariKonKon/ECS/Components/Updateable.hpp"
#include "InariKonKon/Math/Rect.hpp"

namespace ikk
{
    inline static constexpr std::string_view buttonVertexShader = R"(
        #version 460 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec4 color;
        layout(location = 2) in vec2 texCoord;

        out vec4 fragColor;
        out vec2 fragPosWorld;

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
            fragPosWorld = (model * vec3(position.xy, 1.0)).xy;
        })";

    inline static constexpr std::string_view buttonFragmentShader = R"(
        #version 460 core

        in vec4 fragColor;
        in vec2 fragPosWorld;

        out vec4 color;

        uniform mat3 model;
        uniform float cornerRadius; //Goes from 0.0 to 0.5

        void main()
        {
            vec2 fragPos = (inverse(model) * vec3(fragPosWorld, 1.0)).xy;

            vec2 inner = clamp(fragPos, vec2(cornerRadius), vec2(1.0) - vec2(cornerRadius));
            float dist = length(fragPos - inner);
            float alpha = 1.0 - smoothstep(cornerRadius - 0.01, cornerRadius + 0.01, dist);

            if (alpha < 0.01) discard;

            color = vec4(fragColor.rgb, fragColor.a * alpha);
        })";

    Button::Button(std::string_view text, Vec2f position, Vec2f size, Degreef rotation, Color color, float cornerRadius) noexcept
        : Widget(
            { position, size, rotation },
            Model::Square<UIVertex>,
            ShaderProgram{buttonVertexShader, buttonFragmentShader}),
            m_text(text)
    {
        this->getShaderProgram().setUniform("cornerRadius", cornerRadius);

        Updateable update{[this]() noexcept
            {
                if (this->getState() == Button::State::Pressed && this->m_prevState == Button::State::Pressed)
                    this->m_state = Button::State::None;

                this->m_prevState = this->getState();
            }};

        this->addComponent(std::move(update));
    }

    const Button::State& Button::getState() const noexcept
    {
        return this->m_state;
    }

    bool Button::isPressed() const noexcept
    {
        return this->m_state != State::None;
    }

    void Button::onNotify(const MouseEvent::Button& event) noexcept
    {
        if (event.button != Mouse::Button::Left)
            return;

        switch (event.state)
        {
            case Input::State::Pressed:
                if (this->m_hovered == true)
                    this->m_state = State::Held;
                break;
            case Input::State::Released:
                if (this->m_hovered == true)
                        this->m_state = State::Pressed;
                else
                    this->m_state = State::None;
                break;
            case Input::State::Repeat:
            //Mouse can't be repeated, because GLFW does not support it sadly...
                return;
            case Input::State::Unknown:
                return;
        }
    }
    
    void Button::onNotify(const MouseEvent::Move& event) noexcept
    {
        const Transform2D& transform = *this->getComponent<Transform2D>().value();
        const Rectf rect{ transform.getWorldPosition(), transform.getWorldScale() };
        this->m_hovered = rect.contains(event.position, transform.getWorldRotation());

        if (this->m_hovered == false && this->m_state == State::Held)
            this->m_state = State::Withheld;
        else if (this->m_hovered == true && this->m_state == State::Withheld)
            this->m_state = State::Held;
    }
}