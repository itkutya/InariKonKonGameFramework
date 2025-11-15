#include "InariKonKon/Application/Application.hpp"

#include "InariKonKon/ECS/Systems/Transformer.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    Application::Application(std::u8string_view title, Renderer::Type renderer) noexcept
        : m_window({ .renderer = renderer, .title = title, .videomode = { .width = 1024, .height = 800 } })
    {
        DEBUG_LOG("Application created:\n\t{}", *this);
        this->m_deltaTime.restart();
    }

    void Application::run() noexcept
    {
        if (this->m_window.m_window != nullptr)
        {
            while (this->m_window.shouldClose() == false)
            {
                this->handleEvents();
                this->update();
                this->render();
            }
        }
        DEBUG_LOG("Application destroyed.");
    }

    const Window& Application::getWindow() const noexcept
    {
        return this->m_window;
    }

    Window& Application::getWindow() noexcept
    {
        return this->m_window;
    }

    void Application::handleEvents()
    {
        this->m_window.pollEvents();
        for (std::stack<Event>& eventStack = this->m_window.m_eventStack; eventStack.empty() == false; eventStack.pop())
            this->onEvent(eventStack.top());
    }
    
    void Application::update()
    {
        const Time dt = this->m_deltaTime.restart();
        this->onUpdate(dt);
        ECS::update<Transformer>(dt);
    }

    void Application::render() const
    {
        this->m_window.beginRender();
        this->onRender(this->m_window);
        this->m_window.endRender();
    }
}