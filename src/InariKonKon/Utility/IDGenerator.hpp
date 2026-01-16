#pragma once

#include <concepts>

namespace ikk
{
    template<class T>
    concept IntegralIDType = requires { typename T::IDType; } && std::integral<typename T::IDType>;

    template<IntegralIDType T>
    [[nodiscard]] const typename T::IDType getNextAvailableIDfor() noexcept
    {
        static typename T::IDType ID{0};
        return ++ID;
    }
}