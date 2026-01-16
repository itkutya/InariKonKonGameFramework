#pragma once

#include "InariKonKon/Math/Math.hpp"

namespace ikk
{
    template<template<class> class T, class F>
    concept AngleNumber = std::floating_point<F> && (std::is_same_v<T<F>, Degree<F>> || std::is_same_v<T<F>, Radian<F>>);

    template<template<class> class T, std::floating_point F> requires (AngleNumber<T, F>)
    struct [[nodiscard]] Rotation
    {
        T<F> yaw{};
        T<F> pitch{};
        T<F> roll{};
    };

    template<Number T> using RotationDeg = Rotation<Degree, T>;
    template<Number T> using RotationRad = Rotation<Radian, T>;

    using RotationDegf = RotationDeg<float>;
    using RotationDegd = RotationDeg<double>;
    using RotationRadf = RotationRad<float>;
    using RotationRadd = RotationRad<double>;
}