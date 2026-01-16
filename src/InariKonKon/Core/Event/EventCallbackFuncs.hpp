#pragma once

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Utility/Utility.hpp"

struct GLFWwindow;
struct GLFWmonitor;

namespace ikk
{
    class Window;

    class EventCallbackFuncs : public  NonConstructible
    {
#ifdef IKK_DEBUG
        static void errorCallback(int code, const char* description) noexcept;
#endif
        static void windowClosedCallback(GLFWwindow* window) noexcept;

        static void windowResizeCallback(GLFWwindow* window, int width, int height) noexcept;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept;

        static void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) noexcept;

        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept;

        static void windowIconifyCallback(GLFWwindow* window, int iconified) noexcept;

        static void windowMaximizeCallback(GLFWwindow* window, int maximized) noexcept;

        static void windowFocusCallback(GLFWwindow* window, int focused) noexcept;

        static void windowRefreshCallback(GLFWwindow* window) noexcept;

        static void monitorCallback(GLFWmonitor* monitor, int event) noexcept;

        static void cursorEnterCallback(GLFWwindow* window, int entered) noexcept;

        static void characterCallback(GLFWwindow* window, unsigned int codepoint) noexcept;

        static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) noexcept;

        static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;

        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;

        static void joystickCallback(int jid, int event) noexcept;

        static void dropCallback(GLFWwindow* window, int count, const char** paths) noexcept;

        inline static Window* s_eventWindowPtr = nullptr;

        friend class Window;
    };
}