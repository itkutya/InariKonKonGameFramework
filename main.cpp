#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/UI/Button.hpp"

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
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
        window.draw(button);
    }

    ikk::Button button{ikk::Vec2f{ 100.0f, 100.0f }};
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    ikk::Application app{ u8"Title", ikk::Renderer::Type::OpenGL };
    MainMenu mainmenu{};
    mainmenu.attach(app);
    app.run();
}