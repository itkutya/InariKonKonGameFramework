#include "InariKonKon/Utility/Log.hpp"

#include <chrono>
#include <print>

namespace ikk
{
    inline static std::queue<Log::MessageType> s_queue = {};

    const std::queue<Log::MessageType>& Log::getLogs() noexcept
    {
        return s_queue;
    }

    void Log::print(std::string_view msg, Level level, Flags flags) const noexcept
    {
        MessageType message{ msg };

        if ((flags & Flags::Severity) != Flags::None)
            message = std::format("[{}] ", this->convertToString(level)) + message;

        if ((flags & Flags::Date) != Flags::None)
            message = std::format("({:%EY.%Om.%Od. %OH:%OM:%OS}) ", std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now())) + message;

        std::println("{}", message);

        if ((flags & Flags::AddToQueue) != Flags::None)
            s_queue.emplace(std::move(message));
    }
}