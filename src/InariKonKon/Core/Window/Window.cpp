#include "InariKonKon/Core/Window/Window.hpp"

#include "InariKonKon/Core/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep

#include "InariKonKon/Core/Event/EventCallbackFuncs.hpp"

#include "InariKonKon/Graphics/Renderer/OpenGL/OpenGL.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/ECS/Systems/Drawer.hpp"

#include "InariKonKon/Input/InputManager.hpp"

#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    Window::Window(Settings settings) noexcept
        : m_settings(settings)
    {
        switch (this->m_settings.renderer)
        {
            case Renderer::Type::OpenGL:
                this->m_renderer = std::make_shared<OpenGL>();
                break;
            case Renderer::Type::Vulkan:
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                break;
        }

        if (const auto window = createWindow(settings); window.has_value() == true)
        {
            this->m_window = window.value();
            this->setupWindow();
        }
    }

    Window::Window(const Window& other) noexcept
    {
        if (this != &other)
            this->copy(other);
    }

    Window::Window(Window&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
    }

    Window& Window::operator=(const Window& other) noexcept
    {
        if (this != &other)
            this->copy(other);
        return *this;
    }
    
    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
        return *this;
    }

    Window::~Window() noexcept
    {
        if (this->m_window != nullptr)
        {
            glfwDestroyWindow(this->m_window);
            DEBUG_LOG("Window destroyed.");
        }
    }

    const Window::Settings& Window::getSettings() const noexcept
    {
        return this->m_settings;
    }

    Window::Settings& Window::getSettings() noexcept
    {
        return this->m_settings;
    }

    const Vec2f& Window::getContentScale() const noexcept
    {
        return this->m_contentScale;
    }

    const float Window::getAscpectRation() const noexcept
    {
        return static_cast<float>(this->m_settings.videomode.width) / static_cast<float>(this->m_settings.videomode.height);
    }

    const Rectf Window::getViewport() const noexcept
    {
        return Rectf
        {
            0.f,
            0.f,
            static_cast<float>(this->m_settings.videomode.width),
            static_cast<float>(this->m_settings.videomode.height)
        };
    }

    const std::shared_ptr<Renderer>& Window::getRenderer() const noexcept
    {
        return this->m_renderer;
    }

    void Window::lockMouse(bool value) noexcept
    {
        if (value == true)
            glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::draw(const Entity& entity) const noexcept
    {
        if (const std::expected<Drawable*, Error>& drawable = entity.getComponent<Drawable>(); drawable.has_value() == true)
        {
            this->m_renderer->registerEntity(*drawable.value());
            drawable.value()->setActive();
        }
        else
            DEBUG_LOG(Log::Level::Warning, "Entity does not have a drawable component!");
    }

    bool Window::shouldClose() const noexcept
    {
        return BOOL(glfwWindowShouldClose(this->m_window));
    }

    void Window::pollEvents() noexcept
    {
        EventCallbackFuncs::s_eventWindowPtr = this;
        glfwPollEvents();
    }

    void Window::beginRender() const noexcept
    {
        this->m_renderer->newFrame(this->m_settings.clearColor);
        this->m_renderer->updateUnifromBufferObjects(*this);
    }

    void Window::endRender() const noexcept
    {
        ECS::update<Drawer>(*this);
        this->m_renderer->endFrame(*this);
    }

    std::expected<GLFWwindow*, Error> Window::createWindow(const Settings& settings) noexcept
    {
        InputManager::getInstance().checkForConnectedJoysticks();

        if (GLFWwindow* window = glfwCreateWindow(I32(settings.videomode.width), I32(settings.videomode.height),
            TO_ANSI(settings.title.data()), nullptr, nullptr); window != nullptr)
        {
            DEBUG_LOG("Window created: {}", *this);
            return std::expected<GLFWwindow*, Error>{ window };
        }
        else
            return std::unexpected(Error{ "Window cannot be created." });
    }
    
    void Window::setupWindow() noexcept
    {
        if (this->m_window == nullptr)
            return;

        this->m_renderer->createContext(*this);

        glfwSetWindowUserPointer(this->m_window, this);

        if (glfwRawMouseMotionSupported() && this->m_settings.enableRawMouseInput)
            glfwSetInputMode(this->m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        //glfwSwapInterval(0);

#ifdef IKK_DEBUG
        glfwSetErrorCallback(EventCallbackFuncs::errorCallback);
#endif
        glfwSetWindowCloseCallback(this->m_window, EventCallbackFuncs::windowClosedCallback);
        glfwSetWindowSizeCallback(this->m_window, EventCallbackFuncs::windowResizeCallback);
        glfwSetFramebufferSizeCallback(this->m_window, EventCallbackFuncs::framebufferResizeCallback);
        glfwSetWindowPosCallback(this->m_window, EventCallbackFuncs::windowPositionCallback);
        glfwSetWindowIconifyCallback(this->m_window, EventCallbackFuncs::windowIconifyCallback);
        glfwSetWindowMaximizeCallback(this->m_window, EventCallbackFuncs::windowMaximizeCallback);
        glfwSetWindowFocusCallback(this->m_window, EventCallbackFuncs::windowFocusCallback);
        glfwSetCursorEnterCallback(this->m_window, EventCallbackFuncs::cursorEnterCallback);
        glfwSetCharCallback(this->m_window, EventCallbackFuncs::characterCallback);
        glfwSetKeyCallback(this->m_window, EventCallbackFuncs::keyInputCallback);
        glfwSetMouseButtonCallback(this->m_window, EventCallbackFuncs::mouseButtonCallback);
        glfwSetScrollCallback(this->m_window, EventCallbackFuncs::mouseScrollCallback);
        glfwSetCursorPosCallback(this->m_window, EventCallbackFuncs::cursorPositionCallback);
        glfwSetWindowRefreshCallback(this->m_window, EventCallbackFuncs::windowRefreshCallback);
        glfwSetWindowContentScaleCallback(this->m_window, EventCallbackFuncs::windowContentScaleCallback);
        glfwSetDropCallback(this->m_window, EventCallbackFuncs::dropCallback);
        glfwSetMonitorCallback(EventCallbackFuncs::monitorCallback);
        glfwSetJoystickCallback(EventCallbackFuncs::joystickCallback); 

        glfwGetWindowContentScale(this->m_window, &this->m_contentScale.x(), &this->m_contentScale.y());
    }

    void Window::copy(const Window& other) noexcept
    {
        if (other.m_window == nullptr)
            return;

        if (const auto window = createWindow(other.m_settings); window.has_value() == true)
        {
            this->m_window = window.value();
            this->m_eventStack = other.m_eventStack;
            this->m_settings = other.m_settings;
            this->m_renderer = other.m_renderer;
            this->setupWindow();
            DEBUG_LOG("Window copied: {}", *this);
        }
    }

    void Window::move(Window&& other) noexcept
    {
        if (other.m_window == nullptr)
            return;
        
        this->m_window = std::move(other.m_window);
        this->m_eventStack = std::move(other.m_eventStack);
        this->m_settings = std::move(other.m_settings);
        this->m_renderer = std::move(other.m_renderer);
        this->setupWindow();
        DEBUG_LOG("Window moved: {}", *this);
    }
}