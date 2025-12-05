#include "InariKonKon/Application/Application.hpp"

#include <algorithm>

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
        {
            const Event& event = eventStack.top();
            //TODO:
            //Multi-threading?
            std::for_each(this->m_layers.rbegin(), this->m_layers.rend(),
                [&event](Layer* layer) noexcept
                {
                    layer->onEvent(event);
                });
        }
    }
    
    void Application::update()
    {
        const Time dt = this->m_deltaTime.restart();
        std::for_each(this->m_layers.rbegin(), this->m_layers.rend(),
            [&dt](Layer* layer) noexcept
            {
                layer->onUpdate(dt);
            });
    }

    void Application::render() const
    {
        this->m_window.beginRender();
        const Window& window = this->m_window;
        std::for_each(this->m_layers.rbegin(), this->m_layers.rend(),
            [&window](const Layer* layer) noexcept
            {
                layer->onRender(window);
            });
        this->m_window.endRender();
    }
}