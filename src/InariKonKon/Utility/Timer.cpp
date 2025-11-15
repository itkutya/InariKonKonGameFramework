#include "InariKonKon/Utility/Timer.hpp"

#include "InariKonKon/Utility/Log.hpp"

#ifdef IKK_DEBUG

namespace ikk
{
    Profiler::Function::Function(std::string_view description) noexcept
        : m_description(description)
    {
        this->m_clock.restart();
    }

    Profiler::Function::~Function() noexcept
    {
        Log("{}: {}", this->getDescription(), this->getTime().toDuration<std::chrono::milliseconds>());
    }

    const std::string_view& Profiler::Function::getDescription() const noexcept
    {
        return this->m_description;
    }

    const Time Profiler::Function::getTime() const noexcept
    {
        return this->m_clock.getElapsedTime();
    }
}

#endif