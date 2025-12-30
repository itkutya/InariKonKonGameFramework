#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/UI/Widgets/Button.hpp"

class MainMenu final : public ikk::Layer
{
public:
    MainMenu() noexcept
    {
    }

    void onEvent(const ikk::Event& event) noexcept override
    {
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
        button.getComponent<ikk::Transform2D>().value()->rotateLocal(ikk::Degreef{900.f * dt.asSeconds()});
        button.getComponent<ikk::Transform2D>().value()->translateLocal(ikk::Vec2f{50.f, 50.f} * dt.asSeconds());
        button.getComponent<ikk::Transform2D>().value()->translate(ikk::Vec2f{50.f, 50.f} * dt.asSeconds());
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
        window.draw(button);
    }

    ikk::Button button{ikk::Vec2f{ 100.f, 100.f }, ikk::Vec2f{ 100.f, 100.f }, {}, ikk::Color::Blue};
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    ikk::Application app{ u8"Title", ikk::Renderer::Type::OpenGL };
    MainMenu mainmenu{};
    mainmenu.attach(app);
    app.run();
}