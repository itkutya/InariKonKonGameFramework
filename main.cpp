#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Input/Keyboard.hpp"
#include "InariKonKon/Input/Mouse.hpp"
#include "InariKonKon/UI/Button.hpp"

class TestApp : public ikk::Application
{
public:
    TestApp() noexcept
        : ikk::Application(u8"Title", ikk::Renderer::Type::OpenGL), button(this->getWindow())
    {
        drawable.addComponent(ikk::Drawable{ model, vertex, fragment, camera });
        ikk::Transform3D transform{};
        drawable.addComponent(std::move(transform));

        drawable2.addComponent(ikk::Drawable{ model, vertex, fragment, camera });
        ikk::Transform3D transform2{};
        transform2.translateGlobal({1.f, 0.f, 0.f});
        drawable2.addComponent(std::move(transform2));

        camera.getTransform().setParent(*drawable.getComponent<ikk::Transform3D>().value());
        this->getWindow().lockMouse(true);
    }

    void onEvent(const ikk::Event& event) noexcept override
    {
        if (const auto* keyEvent = event.getIf<ikk::KeyboardEvent>(); keyEvent != nullptr)
        {
            if (keyEvent->keycode == ikk::Keyboard::KeyCode::Escape)
            {
                camera.enable(false);
                this->getWindow().lockMouse(false);
            }
        }
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
        camera.processMouseEvent(ikk::Mouse::getCursorPosition(this->getWindow()));
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
        window.draw(drawable);
        window.draw(drawable2);
        //window.draw(button);
    }

    ikk::Button button;

    ikk::Entity drawable{};
    ikk::Entity drawable2{};

    //TODO:
    //Logging!!!
    ikk::Camera camera{ikk::Camera::Type::ThirdPerson, ikk::Vec3f{ 0.f, 0.f, 6.f }, 0.f, 0.f, 0.001f, 1000.f };

    ikk::Model model{
        .m_vertices = {
            { { 0.5f, 0.5f, 0.0f }, ikk::Color::Blue },
            { { 0.5f, -0.5f, 0.0f }, ikk::Color::Green },
            { { -0.5f, -0.5f, 0.0f }, ikk::Color::Blue },
            { { -0.5f, 0.5f, 0.0f }, ikk::Color::Green }
        },
        .m_indices = {
            0, 1, 3,
            1, 2, 3
        }};

    ikk::Shader vertex{ikk::Shader::Type::Vertex, R"(
        #version 460 core

        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec4 aColor;

        out vec4 outColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            outColor = aColor;
        }
    )"};

    ikk::Shader fragment{ikk::Shader::Type::Fragment, R"(
        #version 460 core

        in vec4 outColor;

        out vec4 fragColor;

        void main()
        {
            fragColor = outColor;
        }
    )"};
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    TestApp app{};
    app.run();
}