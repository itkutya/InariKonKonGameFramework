#pragma once

#include <algorithm>
#include <limits>

#include "InariKonKon/Math/Math.hpp"

namespace ikk
{
    template<Number T, T Min = std::numeric_limits<T>::min(), T Max = std::numeric_limits<T>::max()>
    class [[nodiscard]] Clamped final
    {
    public:
        using Type = T;

        [[nodiscard]] constexpr Clamped() noexcept;
        [[nodiscard]] constexpr Clamped(T value) noexcept;

        constexpr Clamped(const Clamped&) noexcept = default;
        constexpr Clamped(Clamped&&) noexcept = default;

        constexpr Clamped& operator=(const Clamped&) noexcept = default;
        constexpr Clamped& operator=(Clamped&&) noexcept = default;

        template<T OtherMin, T OtherMax>
        constexpr Clamped(const Clamped<T, OtherMin, OtherMax>& other) noexcept;
        template<T OtherMin, T OtherMax>
        constexpr Clamped(Clamped<T, OtherMin, OtherMax>&& other) noexcept;

        template<T OtherMin, T OtherMax>
        constexpr Clamped& operator=(const Clamped<T, OtherMin, OtherMax>& other) noexcept;
        template<T OtherMin, T OtherMax>
        constexpr Clamped& operator=(Clamped<T, OtherMin, OtherMax>&& other) noexcept;

        constexpr ~Clamped() noexcept = default;

        [[nodiscard]] constexpr Clamped operator+(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator-(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator*(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator/(const Clamped& value) const noexcept;

        constexpr Clamped& operator+=(const Clamped& value) noexcept;
        constexpr Clamped& operator-=(const Clamped& value) noexcept;
        constexpr Clamped& operator*=(const Clamped& value) noexcept;
        constexpr Clamped& operator/=(const Clamped& value) noexcept;

        [[nodiscard]] constexpr bool operator==(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator<=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator>=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator<(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator>(const Clamped& value) const noexcept;

        [[nodiscard]] constexpr Clamped operator+(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator-(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator*(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator/(T value) const noexcept;

        constexpr Clamped& operator+=(T value) noexcept;
        constexpr Clamped& operator-=(T value) noexcept;
        constexpr Clamped& operator*=(T value) noexcept;
        constexpr Clamped& operator/=(T value) noexcept;

        [[nodiscard]] constexpr bool operator==(T value) const noexcept;
        [[nodiscard]] constexpr bool operator!=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator<=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator>=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator<(T value) const noexcept;
        [[nodiscard]] constexpr bool operator>(T value) const noexcept;

        [[nodiscard]] constexpr T value() const noexcept;
    private:
        T m_value{};

        template<T OtherMin, T OtherMax>
        constexpr const T convertValueFromOtherRange(T value) const noexcept;
    };

    //TODO:
    //Better names...
    using NormalizedFloat   = Clamped<float,  0.f, 1.f>;
    using RangeFloat        = Clamped<float, -1.f, 1.f>;

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>::Clamped() noexcept
        : m_value(Min)
    {
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>::Clamped(T value) noexcept
        : m_value(std::clamp(value, Min, Max))
    {
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>::Clamped(const Clamped<T, OtherMin, OtherMax>& other) noexcept
        : m_value(convertValueFromOtherRange<OtherMin, OtherMax>(other.value()))
    {
    }
    
    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>::Clamped(Clamped<T, OtherMin, OtherMax>&& other) noexcept
        : m_value(convertValueFromOtherRange<OtherMin, OtherMax>(other.value()))
    {
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(const Clamped<T, OtherMin, OtherMax>& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<OtherMin, OtherMax>(other.value());
    }
    
    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(Clamped<T, OtherMin, OtherMax>&& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<OtherMin, OtherMax>(other.value());
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator+(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value + value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator-(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value - value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator*(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value * value.value(), Min, Max) };
    }
    
    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator/(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value / value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator+=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value + value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator-=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value - value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator*=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value * value.value(), Min, Max);
        return *this;
    }
    
    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator/=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value / value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator==(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() == value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator!=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() != value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() <= value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() >= value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() < value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() > value.value();
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator+(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value + value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator-(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value - value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator*(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value * value, Min, Max) };
    }
    
    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator/(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value / value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator+=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value + value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator-=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value - value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator*=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value * value, Min, Max);
        return *this;
    }
    
    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator/=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value / value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator==(T value) const noexcept
    {
        return this->m_value == value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator!=(T value) const noexcept
    {
        return this->m_value != value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<=(T value) const noexcept
    {
        return this->m_value <= value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>=(T value) const noexcept
    {
        return this->m_value >= value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<(T value) const noexcept
    {
        return this->m_value < value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>(T value) const noexcept
    {
        return this->m_value > value;
    }

    template<Number T, T Min, T Max>
    constexpr T Clamped<T, Min, Max>::value() const noexcept
    {
        return this->m_value;
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr const T Clamped<T, Min, Max>::convertValueFromOtherRange(T value) const noexcept
    {
        constexpr T OtherRange = OtherMax - OtherMin;
        constexpr T Range = Max - Min;
        return OtherRange == 0 ? Min : (((value - OtherMin) * Range) / OtherRange) + Min;
    }
}