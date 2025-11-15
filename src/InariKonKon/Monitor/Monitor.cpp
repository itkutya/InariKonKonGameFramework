#include "InariKonKon/Monitor/Monitor.hpp"

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Utility/Utility.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    Monitor::Monitor(bool primary) noexcept
    {
        if (primary == true)
            this->initializeMonitor(glfwGetPrimaryMonitor());
    }

    const std::string_view& Monitor::getName() const noexcept
    {
        return this->m_name;
    }
    
    const VideoMode& Monitor::getActiveVideoMode() const noexcept
    {
        return this->m_videoModes.at(this->m_activeVideoMode);
    }
    
    const std::vector<VideoMode>& Monitor::getVideoModes() const noexcept
    {
        return this->m_videoModes;
    }

    std::vector<Monitor> Monitor::getMonitors() noexcept
    {
        int count = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&count);

        std::vector<Monitor> temp = {};
        temp.reserve(count);

        for (std::size_t i = 0; i < count; ++i)
            temp.emplace_back(false).initializeMonitor(monitors[i]);

        return temp;
    }

    void Monitor::initializeMonitor(GLFWmonitor* monitor) noexcept
    {
        if (monitor == nullptr)
        {
            DEBUG_LOG(Log::Level::Error, "Cannot initialize monitor");
            return;
        }

        this->m_monitor = monitor;
        this->m_name = glfwGetMonitorName(this->m_monitor);

        int count = 0;
        const GLFWvidmode* videoModes = glfwGetVideoModes(this->m_monitor, &count);
        if (count < 1)
        {
            DEBUG_LOG(Log::Level::Error, "Failed to get monitor video modes.");
            return;
        }

        const GLFWvidmode* videoMode = glfwGetVideoMode(this->m_monitor);
        if (videoMode == nullptr)
        {
            DEBUG_LOG(Log::Level::Error, "Failed to get monitor video mode.");
            return;
        }

        for (std::size_t i = 0; i < count; ++i)
        {
            static const auto compare = [](const GLFWvidmode* lhs, const GLFWvidmode* rhs) noexcept
            {
                return (lhs->redBits == rhs->redBits && lhs->greenBits == rhs->greenBits && lhs->blueBits == rhs->blueBits &&
                        lhs->width == rhs->width && lhs->height == rhs->height && lhs->refreshRate == rhs->refreshRate);
            };

            if (compare(videoMode, &videoModes[i]))
                this->m_activeVideoMode = i;

            static auto convert = [](const GLFWvidmode* videomode) noexcept
            {
                return VideoMode
                {
                    .redBits = U8(videomode->redBits), .greenBits = U8(videomode->greenBits), .blueBits = U8(videomode->blueBits),
                    .width = U16(videomode->width), .height = U16(videomode->height), .refreshRate = U16(videomode->refreshRate),
                };
            };

            this->m_videoModes.emplace_back(std::move(convert(&videoModes[i])));
        }

        DEBUG_LOG("Monitor created.\n\tname: {}\n\tactive video mode: {}", this->getName(), this->getActiveVideoMode());
    }
}