#include "InariKonKon/InariKonKon.hpp"

class MainMenu final : public ikk::Layer
{
public:
    void onEvent(const ikk::Event& event) noexcept override
    {
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
    }
};

int main()
{
    INARIKONKON_ENSURE_INIT;
    ikk::Application app{ u8"Title", ikk::Renderer::Type::OpenGL };
    MainMenu mainmenu{};
    mainmenu.attach(app);
    app.run();
}