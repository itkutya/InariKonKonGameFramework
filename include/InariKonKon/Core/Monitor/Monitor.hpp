#pragma once

#include <string_view>
#include <cstddef>
#include <vector>

#include "InariKonKon/Core/Monitor/VideoMode.hpp"

struct GLFWmonitor;

namespace ikk
{
    class [[nodiscard]] Monitor final
    {
    public:
        Monitor(bool primary = true) noexcept;

        Monitor(const Monitor&) noexcept = default;
        Monitor(Monitor&&) noexcept = default;

        Monitor& operator=(const Monitor&) noexcept = default;
        Monitor& operator=(Monitor&&) noexcept = default;

        ~Monitor() noexcept = default;

        const std::string_view& getName() const noexcept;
        const VideoMode& getActiveVideoMode() const noexcept;
        const std::vector<VideoMode>& getVideoModes() const noexcept;

        //TODO:
        //Get content scale & other stuff...

        [[nodiscard]] static std::vector<Monitor> getMonitors() noexcept;
    private:
        GLFWmonitor* m_monitor = nullptr;

        std::string_view m_name = {};
        std::size_t m_activeVideoMode = 0;
        std::vector<VideoMode> m_videoModes = {};

        void initializeMonitor(GLFWmonitor* monitor) noexcept;
    };
}