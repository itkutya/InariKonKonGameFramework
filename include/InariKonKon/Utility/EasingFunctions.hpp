#pragma once

#include <concepts>
#include <numbers>
#include <cmath>

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Utility/Clamped.hpp"

namespace ikk
{
    struct EasingFuncs : public NonConstructible
    {
        struct EaseOut : public NonConstructible
        {
            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Sine(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return std::sin((x.value() * std::numbers::pi_v<T>) / T{2.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quad(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::pow(T{1.f} - x.value(), T{2.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Cubic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::pow(T{1.f} - x.value(), T{3.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quart(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::pow(T{1.f} - x.value(), T{4.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quint(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::pow(T{1.f} - x.value(), T{5.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Circ(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return std::sqrt(T{1.f} - std::pow(x.value() - T{1.f}, T{2.f}));
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Elastic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c4 = (T{2.f} * std::numbers::pi_v<T>) / T{3.f};
                return x == T{0.f} ? T{0.f} : x == T{1.f} ? T{1.f} :
                    std::pow(T{2.f}, T{-10.f} * x.value()) * std::sin((x.value() * T{10.f} - T{0.75f}) * c4) + T{1.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Expo(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x == T{1.f} ? T{1.f} : T{1.f} - std::pow(T{2.f}, T{-10.f} * x.value());
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Back(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c1 = T{1.70158f};
                constexpr auto c3 = c1 + T{1.f};
                return T{1.f} + c3 * std::pow(x.value() - T{1.f}, T{3.f}) + c1 * std::pow(x.value() - T{1.f}, T{2.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Bounce(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto n1 = T{7.5625f};
                constexpr auto d1 = T{2.75f};

                if (x < T{1.f} / d1)
                    return n1 * x.value() * x.value();
                else if (x < T{2.f} / d1)
                {
                    const T newValue = x.value() - T{1.5f} / d1;
                    return n1 * newValue * newValue + T{0.75f};
                }
                else if (x < T{2.5f} / d1)
                {
                    const T newValue = x.value() - T{2.25f} / d1;
                    return n1 * newValue * newValue + T{0.9375f};
                }
                else
                {
                    const T newValue = x.value() - T{2.625f} / d1;
                    return n1 * newValue * newValue + T{0.984375f};
                }
            }
        };

        struct EaseIn : public NonConstructible
        {
            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Sine(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::cos((x.value() * std::numbers::pi_v<T>) / T{2.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quad(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x.value() * x.value();
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Cubic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x.value() * x.value() * x.value();
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quart(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x.value() * x.value() * x.value() * x.value();
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quint(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x.value() * x.value() * x.value() * x.value() * x.value();
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Circ(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - std::sqrt(T{1.f} - (x.value() * x.value()));
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Elastic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c4 = (T{2.f} * std::numbers::pi_v<T>) / T{3.f};
                return x == T{0.f} ? T{0.f} : x == T{1.f} ? T{1.f} :
                    -std::pow(T{2.f}, T{10.f} * x.value() - T{10.f}) * std::sin(x.value() * T{10.f} - T{10.75f} * c4);
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Expo(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x == T{0.f} ? T{0.f} : std::pow(T{2.f}, T{10.f} * x.value() - T{10.f});
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Back(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c1 = T{1.70158f};
                constexpr auto c3 = c1 + T{1.f};
                return c3 * x.value() * x.value() * x.value() - c1 * x.value() * x.value();
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Bounce(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return T{1.f} - EasingFuncs::EaseOut::Bounce<T>(T{1.f} - x.value());
            }
        };

        struct EaseInOut : public NonConstructible
        {
            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Sine(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return -(std::cos(std::numbers::pi_v<T> * x.value()) - T{1.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quad(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ? T{4.f} * x.value() * x.value() : T{1.f} - std::pow(-T{2.f} * x.value() + T{2.f}, T{2.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Cubic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ? T{4.f} * x.value() * x.value() * x.value() : T{1.f} - std::pow(T{-2.f} * x.value() + T{2.f}, T{3.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quart(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ?
                    T{16.f} * x.value() * x.value() * x.value() * x.value() :
                    T{1.f} - std::pow(T{-2.f} * x.value() + T{2.f}, T{4.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Quint(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ?
                    T{4.f} * x.value() * x.value() * x.value() * x.value() * x.value() :
                    T{1.f} - std::pow(T{-2.f} * x.value() + T{2.f}, T{5.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Circ(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ?
                    (T{1.f} - std::sqrt(T{1.f} - std::pow(T{2.f} * x.value(), T{2.f}))) / T{2.f} :
                    (std::sqrt(T{1.f} - std::pow(T{-2.f} * x.value() + T{2.f}, T{2.f})) + T{1.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Elastic(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c5 = (T{2.f} * std::numbers::pi_v<T>) / T{4.5f};
                return x == T{0.f} ? T{0.f} : x == T{1.f} ? T{1.f} : x < T{0.5f} ?
                    -(std::pow(T{2.f}, T{20.f} * x.value() - T{10.f}) * std::sin((T{20.f} * x.value() - T{11.125f}) * c5)) / T{2.f} :
                    (std::pow(T{2.f}, T{-20.f} * x.value() + T{10.f}) * std::sin((T{20.f} * x.value() - T{11.125f}) * c5)) / T{2.f} + T{1.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Expo(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x == T{0.f} ? T{0.f} : x == T{1.f} ? T{1.f} : x < T{0.5f} ?
                    std::pow(T{2.f}, T{20.f} * x.value() - T{10.f}) / T{2.f} : (T{2.f} - std::pow(T{2.f}, T{-20.f} * x.value() + T{10.f})) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Back(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                constexpr auto c1 = T{1.70158f};
                constexpr auto c2 = c1 * T{1.525f};
                return x < T{0.5f} ?
                    (std::pow(T{2.f} * x.value(), T{2.f}) * ((c2 + T{1.f}) * T{2.f} * x.value() - c2)) / T{2.f} :
                    (std::pow(T{2.f} * x.value() - T{2.f}, T{2.f}) * ((c2 + T{1.f}) * (x.value() * T{2.f} - T{2.f}) + c2) + T{2.f}) / T{2.f};
            }

            template<std::floating_point T>
            [[nodiscard]] inline static constexpr T Bounce(const Clamped<T, T{0.f}, T{1.f}>& x) noexcept
            {
                return x < T{0.5f} ?
                    (T{1.f} - EasingFuncs::EaseOut::Bounce<T>(T{1.f} - T{2.f} * x.value())) / T{2.f} :
                    (T{1.f} + EasingFuncs::EaseOut::Bounce<T>(T{2.f} * x.value() - T{1.f})) / T{2.f};
            }
        };
    };
}