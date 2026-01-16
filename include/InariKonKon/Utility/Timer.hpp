#pragma once

#include <string_view>

#include "InariKonKon/Utility/Clock.hpp"

namespace ikk
{
    struct Profiler final
    {
        class Function final
        {
        public:
            Function(std::string_view description) noexcept;

            Function(const Function&) noexcept = default;
            Function(Function&&) noexcept = default;

            Function& operator=(const Function&) noexcept = default;
            Function& operator=(Function&&) noexcept = default;

            ~Function() noexcept;

            [[nodiscard]] const std::string_view& getDescription() const noexcept;
            [[nodiscard]] const Time getTime() const noexcept;
        private:
            std::string_view m_description;
            Clock m_clock;
        };
    };
}

#ifdef IKK_DEBUG
    #define PROFILE_FUNCTION(description) [[maybe_unused]] ikk::Profiler::Function _ { description }
#else
    #define PROFILE_FUNCTION(description) ((void)0)
#endif