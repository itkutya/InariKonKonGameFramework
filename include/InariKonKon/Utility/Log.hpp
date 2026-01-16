#pragma once

#include <string_view>
#include <utility>
#include <string>
#include <format>
#include <queue>

#include "InariKonKon/Utility/NonCopyable.hpp"
#include "InariKonKon/Utility/NonMovable.hpp"
#include "InariKonKon/Utility/Utility.hpp"

namespace ikk
{
    class Log final : public NonCopyable, public NonMovable
    {
    public:
        typedef std::string MessageType;

        enum struct Level : std::uint8_t
        {
            Info = 0,
            Warning,
            Error,
            Fatal
        };

        enum struct Flags : std::uint32_t
        {
            None        = 0 << 0,
            Date        = 1 << 0,
            Severity    = 1 << 1,
            AddToQueue  = 1 << 2,
            All         = None | Date | Severity | AddToQueue
        };

        template<class... Args>
        Log(Level level, Flags flags, const std::format_string<Args...> fmt, Args&&... args) noexcept;

        template<class... Args>
        Log(Level level, const std::format_string<Args...> fmt, Args&&... args) noexcept;

        template<class... Args>
        Log(const std::format_string<Args...> fmt, Args&&... args) noexcept;

        ~Log() noexcept = default;

        //TODO:
        //Add a save function for json files...

        [[nodiscard]] static const std::queue<Log::MessageType>& getLogs() noexcept;
    private:
        void print(std::string_view msg, Level level, Flags flags) const noexcept;

        [[nodiscard]] constexpr std::string_view convertToString(Level level) const noexcept;
        
        template<class... Args>
        friend constexpr auto makeFormat(const std::format_string<Args...> fmt, Args&&... args) noexcept;
    };

    template<class... Args>
    Log::Log(Level level, Flags flags, const std::format_string<Args...> fmt, Args&&... args) noexcept
    {
        this->print(std::vformat(fmt.get(), std::make_format_args(args...)), level, flags);
    }

    template<class... Args>
    Log::Log(Level level, const std::format_string<Args...> fmt, Args&&... args) noexcept
        : Log(level, Log::Flags::All, fmt, std::forward<Args>(args)...)
    {
    }

    template<class... Args>
    Log::Log(const std::format_string<Args...> fmt, Args&&... args) noexcept
        : Log(Log::Level::Info, Log::Flags::All, fmt, std::forward<Args>(args)...)
    {
    }

    constexpr std::string_view Log::convertToString(Level level) const noexcept
    {
        switch (level)
        {
        case Level::Info:
            return "INFO";
        case Level::Warning:
            return "WARNING";
        case Level::Error:
            return "ERROR";
        case Level::Fatal:
            return "FATAL";
        }
        return "";
    }

    constexpr Log::Flags operator|(Log::Flags lhs, Log::Flags rhs) noexcept
    {
        return static_cast<Log::Flags>(std::to_underlying(lhs) | std::to_underlying(rhs));
    }

    constexpr Log::Flags operator&(Log::Flags lhs, Log::Flags rhs) noexcept
    {
        return static_cast<Log::Flags>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }

    #ifdef IKK_DEBUG
        #define DEBUG_LOG(...) [[maybe_unused]] const ikk::Log _{ __VA_ARGS__ }
    #else
        #define DEBUG_LOG(...) ((void)0)
    #endif
}