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
        //TODO:
        //This in the class...
        static ikk::Button::State btnState = ikk::Button::State::None;

        if (button.getState() == ikk::Button::State::Pressed && btnState == ikk::Button::State::Pressed)
            button.m_state = ikk::Button::State::None;

        btnState = button.getState();
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
        window.draw(button);
    }

    ikk::Button button{"Button", { 100.f, 100.f }, { 100.f, 100.f }, {25.f}, ikk::Color::Miku};
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    ikk::Application app{ u8"Title", ikk::Renderer::Type::OpenGL };
    MainMenu mainmenu{};
    mainmenu.attach(app);
    app.run();
}