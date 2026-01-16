#pragma once

#include "InariKonKon/Utility/NonCopyable.hpp"
#include "InariKonKon/Utility/NonMovable.hpp"

namespace ikk
{
    class NonConstructible : public NonCopyable, public NonMovable
    {
    public:
        constexpr NonConstructible() noexcept = delete;
        
        virtual constexpr ~NonConstructible() noexcept = default;
    private:
    };
}