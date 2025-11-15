#include "InariKonKon/Event/EventCallbackFuncs.hpp"

#include <filesystem>
#include <string>

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Input/InputManager.hpp"
#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
#ifdef IKK_DEBUG
    void EventCallbackFuncs::errorCallback(int code, const char* description) noexcept
    {
        DEBUG_LOG(Log::Level::Error, "{}: {}", code, description);
    }
#endif
    void EventCallbackFuncs::windowClosedCallback(GLFWwindow* window) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::Closed{});
            DEBUG_LOG("Window closed:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
        }
    }

    void EventCallbackFuncs::windowResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::Resized{ .width = U32(width), .height = U32(height) });
            windowPtr->m_renderer->onWindowResize({ U32(width), U32(height) });

            DEBUG_LOG("Window resized:\n\tx: {}\n\ty: {}", width, height);
        }
    }

    void EventCallbackFuncs::framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::FramebufferResized{ .width = U32(width), .height = U32(height) });
            windowPtr->m_renderer->onFramebufferResize({ U32(width), U32(height) });

            DEBUG_LOG("Framebuffer resized:\n\tx: {}\n\ty: {}", width, height);
        }
    }

    void EventCallbackFuncs::windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::ContentScale{ .scale = { xscale, yscale } });
            windowPtr->m_contentScale = { xscale, yscale };
            DEBUG_LOG("Content scale changed:\n\tx: {}\n\ty: {}", xscale, yscale);
        }
    }

    void EventCallbackFuncs::windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::Position{ .x = U32(xpos), .y = U32(ypos) });
            DEBUG_LOG("Window position changed:\n\tx: {}\n\ty: {}", xpos, ypos);
        }
    }

    void EventCallbackFuncs::windowIconifyCallback(GLFWwindow* window, int iconified) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            if (iconified == GLFW_TRUE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::Iconified{});
                DEBUG_LOG("Window iconified:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
            else if (iconified == GLFW_FALSE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::UnIconified{});
                DEBUG_LOG("Window uniconified:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
        }
    }

    void EventCallbackFuncs::windowMaximizeCallback(GLFWwindow* window, int maximized) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            if (maximized == GLFW_TRUE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::Maximized{});
                DEBUG_LOG("Window maximized:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
            else if (maximized == GLFW_FALSE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::Minimized{});
                DEBUG_LOG("Window minimized:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
        }
    }

    void EventCallbackFuncs::windowFocusCallback(GLFWwindow* window, int focused) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            if (focused == GLFW_TRUE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::FocusGained{});
                DEBUG_LOG("Window focus gained:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
            else if (focused == GLFW_FALSE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::FocusLost{});
                DEBUG_LOG("Window focus lost:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
        }
    }

    void EventCallbackFuncs::windowRefreshCallback(GLFWwindow* window) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Window::Refreshed{});
            DEBUG_LOG("Window refreshed:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
        }
    }

    void EventCallbackFuncs::monitorCallback(GLFWmonitor* monitor, int event) noexcept
    {
        if (s_eventWindowPtr == nullptr)
            return;

        if (event == GLFW_CONNECTED)
        {
            s_eventWindowPtr->m_eventStack.emplace(Event::Monitor::Connected{ });
            DEBUG_LOG("Monitor connected:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(monitor));
        }
        else if (event == GLFW_DISCONNECTED)
        {
            s_eventWindowPtr->m_eventStack.emplace(Event::Monitor::Disconnected{ });
            DEBUG_LOG("Monitor disconnected:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(monitor));
        }
    }

    void EventCallbackFuncs::cursorEnterCallback(GLFWwindow* window, int entered) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            if (entered == GLFW_TRUE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::CursorEntered{});
                DEBUG_LOG("Window cursor entered:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
            else if (entered == GLFW_FALSE)
            {
                windowPtr->m_eventStack.emplace(Event::Window::CursorLeft{});
                DEBUG_LOG("Window cursor left:\n\tptr: {:#x}", reinterpret_cast<std::uintptr_t>(window));
            }
        }
    }

    void EventCallbackFuncs::characterCallback(GLFWwindow* window, unsigned int codepoint) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            static const auto convertUnicodeToUTF8 = [](std::uint32_t codepoint) noexcept
            {
                std::string out;
                if (codepoint <= 0x7f)
                    out.append(1, static_cast<char>(codepoint));
                else if (codepoint <= 0x7ff)
                {
                    out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
                    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
                }
                else if (codepoint <= 0xffff)
                {
                    out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
                    out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
                    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
                }
                else
                {
                    out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
                    out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
                    out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
                    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
                }
                return out;
            };

            windowPtr->m_eventStack.emplace(Event::Input::Text{ .unicode = codepoint });
            DEBUG_LOG("Text entered:\n\tUTF8: {}", convertUnicodeToUTF8(codepoint));
        }
    }

    void EventCallbackFuncs::keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            const Keyboard::KeyCode keycode = Keyboard::convertFromGLFWKeyCode(key);
            const Input::State state = Input::convertFromGLFWAction(action);

            windowPtr->m_eventStack.emplace(Event::Input::Keyboard{ .keycode = keycode, .scancode = scancode, .state = state });

            DEBUG_LOG("Key pressed:\n\tKeycode: {}\n\tScancode: {}\n\tState: {}",
                Keyboard::convertToString(keycode), scancode, Input::convertToString(state));
        }
    }

    void EventCallbackFuncs::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            const Mouse::Button mButton = Mouse::convertFromGLFWButton(button);
            const Input::State state = Input::convertFromGLFWAction(action);

            windowPtr->m_eventStack.emplace(Event::Input::Mouse::Button{ .button = mButton, .state = state });

            DEBUG_LOG("Mouse button pressed:\n\tButton: {}\n\tState: {}",
                Mouse::convertToString(mButton), Input::convertToString(state));
        }
    }

    void EventCallbackFuncs::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            if (xoffset != 0)
                windowPtr->m_eventStack.emplace(Event::Input::Mouse::Wheel{ .wheel = Mouse::Wheel::Horizontal, .delta = xoffset });

            if (yoffset != 0)
                windowPtr->m_eventStack.emplace(Event::Input::Mouse::Wheel{ .wheel = Mouse::Wheel::Vertical, .delta = yoffset });

            DEBUG_LOG("Mouse wheel event:\n\tHorizontal offset: {}\n\tVertical offset: {}", xoffset, yoffset);
        }
    }

    void EventCallbackFuncs::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            windowPtr->m_eventStack.emplace(Event::Input::Mouse::Move{ .position = { xpos, ypos } });
            DEBUG_LOG("Mouse moved:\n\tx: {}\n\ty: {}", xpos, ypos);
        }
    }

    void EventCallbackFuncs::joystickCallback(int jid, int event) noexcept
    {
        if (s_eventWindowPtr == nullptr)
            return;

        if (event == GLFW_CONNECTED)
        {
            s_eventWindowPtr->m_eventStack.emplace(Event::Input::Joystick::Connected{ .id = U32(jid) });
            InputManager::getInstance().addJoystick(jid);
            DEBUG_LOG("Joystick connected:\n\tID: {}", jid);
        }
        else if (event == GLFW_DISCONNECTED)
        {
            s_eventWindowPtr->m_eventStack.emplace(Event::Input::Joystick::Disconnected{ .id = U32(jid) });
            InputManager::getInstance().removeJoystick(jid);
            DEBUG_LOG("Joystick disconnected:\n\tID: {}", jid);
        }
    }

    void EventCallbackFuncs::dropCallback(GLFWwindow* window, int count, const char** paths) noexcept
    {
        if (Window* windowPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); windowPtr != nullptr)
        {
            std::vector<std::filesystem::path> files{};
            files.reserve(count);
            for (std::size_t i = 0; i < count; ++i)
                files.emplace_back(std::filesystem::path{ paths[i] });

            windowPtr->m_eventStack.emplace(Event::Window::FileDroped{ .paths = std::move(files) });
            //TODO: c++26
            DEBUG_LOG("File(s) droped:\n\tFile path(s):");
            for (const std::filesystem::path& file : files)
                DEBUG_LOG("{}", file.string().c_str());
        }
    }
}