#pragma once

#include <expected>

#include "InariKonKon/Utility/Singleton.hpp"
#include "InariKonKon/Utility/Error.hpp"

namespace ikk
{
    class ExternalLibraries final : public Singleton<ExternalLibraries>
    {
    public:
        ~ExternalLibraries() noexcept;

        [[nodiscard]] std::expected<void, Error> init();
    private:
        ExternalLibraries() noexcept = default;

        bool m_initialized = false;
        
        friend Singleton<ExternalLibraries>;
    };
}