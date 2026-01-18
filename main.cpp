#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/UI/Widgets/Button.hpp"

class MainMenu final : public ikk::Layer
{
public:
    MainMenu() noexcept
        : text(font, U"Hello World", { 255.f, 155.f }, {1.f, 1.f}, {}, ikk::Color::Teto)
    {
    }

    void onEvent(const ikk::Event& event) noexcept override
    {
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
        if (button.getState() == ikk::Button::State::Held)
            button.setColor(ikk::Color::Teto);
        else
            button.setColor(ikk::Color::Miku);
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
        window.draw(button);
        window.draw(button.m_text);
        window.draw(text);
    }

    ikk::Button button{U"Button", { 100.f, 100.f }, { 100.f, 100.f }, {25.f}, ikk::Color::Miku, 0.3f};
    ikk::Font font{ikk::File{"/home/itkutya/Documents/c++/InariKonKon/resources/BaeFont-Regular.ttf"}, 32};
    ikk::Text text;
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    ikk::Application app{ u8"Title", ikk::Renderer::Type::OpenGL };
    MainMenu mainmenu{};
    mainmenu.attach(app);
    app.run();
}