#pragma once

#include "InariKonKon/Utility/Time.hpp"

namespace ikk
{
    class [[nodiscard]] Clock final
    {
    public:
        [[nodiscard]] Clock() noexcept = default;

        ~Clock() noexcept = default;

        Clock(const Clock&) noexcept = default;
        Clock(Clock&&) noexcept = default;

        Clock& operator=(const Clock&) noexcept = default;
        Clock& operator=(Clock&&) noexcept = default;

        void start() noexcept;
        void stop() noexcept;
        void waitFor(Time time) const noexcept;

        [[nodiscard]] Time getElapsedTime() const noexcept;
        [[nodiscard]] bool isRunning() const noexcept;

        Time restart() noexcept;
        Time reset() noexcept;
    private:
        std::chrono::steady_clock::time_point m_startPoint	{ std::chrono::steady_clock::now() };
        std::chrono::steady_clock::time_point m_stopPoint	{};
    };
}