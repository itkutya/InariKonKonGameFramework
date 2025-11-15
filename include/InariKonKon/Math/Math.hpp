#ifndef IKK_MATH_HPP
#define IKK_MATH_HPP

#include <type_traits>
#include <concepts>
#include <numbers>
#include <cstdint>
#include <cstdlib>
#include <limits>

namespace ikk
{
    enum struct MatrixOrdering : std::uint8_t
    {
        RowMajor, ColumnMajor
    };

    enum struct Dimension : std::uint8_t
    {
        _2D, _3D
    };

    template<std::floating_point T>
    struct [[nodiscard]] Degree final
    {
        using Type = T;
        T value = 0.f;
    };

    using Degreef = Degree<float>;
    using Degreed = Degree<double>;

    template<std::floating_point T>
    struct [[nodiscard]] Radian final
    {
        using Type = T;
        T value = 0.f;
    };

    using Radianf = Radian<float>;
    using Radiand = Radian<double>;

    template<std::floating_point T>
    [[nodiscard]] inline constexpr Degree<T> toDegree(Radian<T> rad) noexcept
    {
        return Degree<T>{ .value = rad.value * (static_cast<T>(180.f) / std::numbers::pi_v<T>) };
    }

    template<std::floating_point T>
    [[nodiscard]] inline constexpr Radian<T> toRadian(Degree<T> deg) noexcept
    {
        return Radian<T>{ .value = deg.value * (std::numbers::pi_v<T> / static_cast<T>(180.f)) };
    }

    template<class T>
    concept BasicNumber = (std::is_arithmetic<T>::value == true && std::is_same<T, bool>::value == false);

    template<class T>
    concept Number = BasicNumber<T> || BasicNumber<typename T::Type>;

    template<Number T>
    [[nodiscard]] inline constexpr bool isZero(T value, T tolerance = std::numeric_limits<T>::epsilon()) noexcept
    {
        if constexpr (std::is_floating_point<T>::value)
            return std::abs(value) <= tolerance;
        else
            return value == T{0};
    }
}

#endif