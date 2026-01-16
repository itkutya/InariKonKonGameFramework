#pragma once

#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <format>
#include <array>
#include <cmath>
#include <span>

#include "InariKonKon/Math/Math.hpp"

namespace ikk
{
    template<std::size_t N, Number T>
    class Vec final
    {
        static_assert(N >= 1);
    public:
        using Type = T;

        constexpr Vec() noexcept = default;
        constexpr Vec(T value) noexcept;
        constexpr Vec(std::span<T, N> span) noexcept;
        constexpr Vec(std::array<T, N> array) noexcept;
        constexpr Vec(std::initializer_list<T> list) noexcept;

        constexpr Vec(const Vec&) noexcept = default;
        constexpr Vec(Vec&&) noexcept = default;

        constexpr Vec& operator=(const Vec&) noexcept = default;
        constexpr Vec& operator=(Vec&&) noexcept = default;

        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec(const Vec<N, U>& other) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec(Vec<N, U>&& other) noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator=(const Vec<N, U>& other) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator=(Vec<N, U>&& other) noexcept;

        constexpr ~Vec() noexcept = default;

        [[nodiscard]] static constexpr Vec X() noexcept requires (N >= 1);
        [[nodiscard]] static constexpr Vec Y() noexcept requires (N >= 2);
        [[nodiscard]] static constexpr Vec Z() noexcept requires (N >= 3);
        [[nodiscard]] static constexpr Vec W() noexcept requires (N >= 4);

        [[nodiscard]] constexpr const T& at(std::size_t index) const noexcept;
        [[nodiscard]] constexpr T& at(std::size_t index) noexcept;

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept;
        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept;

        [[nodiscard]] constexpr const T& x() const noexcept requires (N >= 1);
        [[nodiscard]] constexpr const T& y() const noexcept requires (N >= 2);
        [[nodiscard]] constexpr const T& z() const noexcept requires (N >= 3);
        [[nodiscard]] constexpr const T& w() const noexcept requires (N >= 4);

        [[nodiscard]] constexpr T& x() noexcept requires (N >= 1);
        [[nodiscard]] constexpr T& y() noexcept requires (N >= 2);
        [[nodiscard]] constexpr T& z() noexcept requires (N >= 3);
        [[nodiscard]] constexpr T& w() noexcept requires (N >= 4);

        [[nodiscard]] constexpr Vec operator+() const noexcept;
        [[nodiscard]] constexpr Vec operator-() const noexcept;

        [[nodiscard]] constexpr Vec operator+(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr Vec operator-(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr Vec operator*(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr Vec operator/(const Vec& rhs) const noexcept;

        constexpr Vec operator+(T scalar) const noexcept;
        constexpr Vec operator-(T scalar) const noexcept;
        constexpr Vec operator*(T scalar) const noexcept;
        constexpr Vec operator/(T scalar) const noexcept;

        constexpr Vec& operator+=(const Vec& rhs) noexcept;
        constexpr Vec& operator-=(const Vec& rhs) noexcept;
        constexpr Vec& operator*=(const Vec& rhs) noexcept;
        constexpr Vec& operator/=(const Vec& rhs) noexcept;

        constexpr Vec& operator+=(T scalar) noexcept;
        constexpr Vec& operator-=(T scalar) noexcept;
        constexpr Vec& operator*=(T scalar) noexcept;
        constexpr Vec& operator/=(T scalar) noexcept;

        [[nodiscard]] constexpr bool operator==(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr bool operator<(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr bool operator>(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr bool operator<=(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr bool operator>=(const Vec& rhs) const noexcept;

        [[nodiscard]] constexpr T dot(const Vec& rhs) const noexcept;
        [[nodiscard]] constexpr T distance(const Vec& rhs) const noexcept;

        [[nodiscard]] constexpr T length_squared() const noexcept;
        [[nodiscard]] constexpr T length() const noexcept;

        constexpr void normalize() noexcept;
        [[nodiscard]] constexpr Vec normalized() const noexcept;

        [[nodiscard]] constexpr T cross(const Vec& rhs) const noexcept requires (N == 2);
        [[nodiscard]] constexpr Vec cross(const Vec& rhs) const noexcept requires (N == 3);

        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr Vec<N, U> operator+(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr Vec<N, U> operator-(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr Vec<N, U> operator*(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr Vec<N, U> operator/(const Vec<N, U>& rhs) const noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, U> operator+(U scalar) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, U> operator-(U scalar) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, U> operator*(U scalar) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, U> operator/(U scalar) const noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator+=(const Vec<N, U>& rhs) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator-=(const Vec<N, U>& rhs) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator*=(const Vec<N, U>& rhs) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator/=(const Vec<N, U>& rhs) noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator+=(U scalar) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator-=(U scalar) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator*=(U scalar) noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        constexpr Vec<N, T>& operator/=(U scalar) noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator==(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator!=(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator<(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator>(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator<=(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr bool operator>=(const Vec<N, U>& rhs) const noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr T dot(const Vec<N, U>& rhs) const noexcept;
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr T distance(const Vec<N, U>& rhs) const noexcept;

        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr T cross(const Vec<N, U>& rhs) const noexcept requires (N == 2);
        template<Number U> requires (std::is_convertible<U, T>::value)
        [[nodiscard]] constexpr Vec<N, T> cross(const Vec<N, U>& rhs) const noexcept requires (N == 3);
    private:
        std::array<T, N> m_data{T{0}};
    };

    template<Number T, Number... Ts>
    Vec(T, Ts...) -> Vec<1 + sizeof...(Ts), T>;

    template<Number T> using Vec2 = Vec<2, T>;
    template<Number T> using Vec3 = Vec<3, T>;
    template<Number T> using Vec4 = Vec<4, T>;

    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;
    using Vec2i = Vec2<std::int32_t>;
    using Vec2I = Vec2<std::int64_t>;
    using Vec2u = Vec2<std::uint32_t>;
    using Vec2U = Vec2<std::uint64_t>;

    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;
    using Vec3i = Vec3<std::int32_t>;
    using Vec3I = Vec3<std::int64_t>;
    using Vec3u = Vec3<std::uint32_t>;
    using Vec3U = Vec3<std::uint64_t>;

    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
    using Vec4i = Vec4<std::int32_t>;
    using Vec4I = Vec4<std::int64_t>;
    using Vec4u = Vec4<std::uint32_t>;
    using Vec4U = Vec4<std::uint64_t>;

    template<std::size_t N, Number T>
    constexpr Vec<N, T>::Vec(T value) noexcept
    {
        this->m_data.fill(value);
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>::Vec(std::span<T, N> span) noexcept
    {
        std::copy(span.begin(), span.end(), this->m_data.begin());
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>::Vec(std::array<T, N> array) noexcept
        : m_data(array)
    {
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>::Vec(std::initializer_list<T> list) noexcept
    {
        assert(list.size() == N);
        std::copy(list.begin(), list.end(), this->m_data.begin());
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>::Vec(const Vec<N, U>& other) noexcept
    {
        for (std::size_t i = 0; i < this->m_data.size(); ++i)
            this->m_data.at(i) = static_cast<T>(other.at(i));
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>::Vec(Vec<N, U>&& other) noexcept
    {
        for (std::size_t i = 0; i < this->m_data.size(); ++i)
            this->m_data.at(i) = std::move(static_cast<T>(other.at(i)));
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator=(const Vec<N, U>& other) noexcept
    {
        for (std::size_t i = 0; i < this->m_data.size(); ++i)
            this->m_data.at(i) = static_cast<T>(other.at(i));
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator=(Vec<N, U>&& other) noexcept
    {
        for (std::size_t i = 0; i < this->m_data.size(); ++i)
            this->m_data.at(i) = std::move(static_cast<T>(other.at(i)));
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::X() noexcept requires (N >= 1)
    {
        Vec<N, T> v{};
        v.m_data.at(0) = T{1};
        return v;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::Y() noexcept requires (N >= 2)
    {
        Vec<N, T> v{};
        v.m_data.at(1) = T{1};
        return v;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::Z() noexcept requires (N >= 3)
    {
        Vec<N, T> v{};
        v.m_data.at(2) = T{1};
        return v;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::W() noexcept requires (N >= 4)
    {
        Vec<N, T> v{};
        v.m_data.at(3) = T{1};
        return v;
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::x() const noexcept requires (N >= 1)
    {
        return m_data.at(0);
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::y() const noexcept requires (N >= 2)
    {
        return m_data.at(1);
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::z() const noexcept requires (N >= 3)
    {
        return m_data.at(2);
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::w() const noexcept requires (N >= 4)
    {
        return m_data.at(3);
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::x() noexcept requires (N >= 1)
    {
        return m_data.at(0);
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::y() noexcept requires (N >= 2)
    {
        return m_data.at(1);
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::z() noexcept requires (N >= 3)
    {
        return m_data.at(2);
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::w() noexcept requires (N >= 4)
    {
        return m_data.at(3);
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::at(std::size_t index) const noexcept
    {
        assert(index < N);
        return this->m_data.at(index);
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::at(std::size_t index) noexcept
    {
        assert(index < N);
        return this->m_data.at(index);
    }

    template<std::size_t N, Number T>
    constexpr const T& Vec<N, T>::operator[](std::size_t index) const noexcept
    {
        assert(index < N);
        return this->m_data[index];
    }

    template<std::size_t N, Number T>
    constexpr T& Vec<N, T>::operator[](std::size_t index) noexcept
    {
        assert(index < N);
        return this->m_data[index];
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator+() const noexcept
    {
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator-() const noexcept
    {
        Vec out{};
        for (std::size_t i = 0; i < N; ++i) out.at(i) = -this->at(i);
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator+(const Vec& rhs) const noexcept
    {
        Vec out = *this;
        out += rhs;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator-(const Vec& rhs) const noexcept
    {
        Vec out = *this;
        out -= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator*(const Vec& rhs) const noexcept
    {
        Vec out = *this;
        out *= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator/(const Vec& rhs) const noexcept
    {
        Vec out = *this;
        out /= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator+(T scalar) const noexcept
    {
        Vec out = *this;
        out += scalar;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator-(T scalar) const noexcept
    {
        Vec out = *this;
        out -= scalar;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator*(T scalar) const noexcept
    {
        Vec out = *this;
        out *= scalar;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::operator/(T scalar) const noexcept
    {
        Vec out = *this;
        out /= scalar;
        return out;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator+=(const Vec& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) += rhs.at(i);
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator-=(const Vec& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) -= rhs.at(i);
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator*=(const Vec& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) *= rhs.at(i);
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator/=(const Vec& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) /= rhs.at(i);
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator+=(T scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) += scalar;
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator-=(T scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) -= scalar;
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator*=(T scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) *= scalar;
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T>& Vec<N, T>::operator/=(T scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) /= scalar;
        return *this;
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator==(const Vec& rhs) const noexcept
    {
        for (std::size_t i = 0; i < N; ++i) if (this->m_data.at(i) != rhs.at(i)) return false;
        return true;
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator!=(const Vec& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator<(const Vec& rhs) const noexcept
    {
        return this->length_squared() < rhs.length_squared();
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator>(const Vec& rhs) const noexcept
    {
        return this->length_squared() > rhs.length_squared();
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator<=(const Vec& rhs) const noexcept
    {
        return this->length_squared() <= rhs.length_squared();
    }

    template<std::size_t N, Number T>
    constexpr bool Vec<N, T>::operator>=(const Vec& rhs) const noexcept
    {
        return this->length_squared() >= rhs.length_squared();
    }

    template<std::size_t N, Number T>
    constexpr T Vec<N, T>::dot(const Vec& rhs) const noexcept
    {
        T sum{};
        for (std::size_t i = 0; i < N; ++i) sum += this->m_data.at(i) * rhs.at(i);
        return sum;
    }

    template<std::size_t N, Number T>
    constexpr T Vec<N, T>::distance(const Vec& rhs) const noexcept
    {
        const Vec diff = *this - rhs;
        return std::sqrt(diff.length_squared());
    }

    template<std::size_t N, Number T>
    constexpr T Vec<N, T>::length_squared() const noexcept
    {
        return this->dot(*this);
    }

    template<std::size_t N, Number T>
    constexpr T Vec<N, T>::length() const noexcept
    {
        return std::sqrt(this->length_squared());
    }

    template<std::size_t N, Number T>
    constexpr void Vec<N, T>::normalize() noexcept
    {
        const T len = this->length();
        if (isZero(len) == false)
            *this /= len;
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::normalized() const noexcept
    {
        Vec out = *this;
        out.normalize();
        return out;
    }

    template<std::size_t N, Number T>
    constexpr T Vec<N, T>::cross(const Vec& rhs) const noexcept requires (N == 2)
    {
        return (this->x() * rhs.y()) - (this->y() * rhs.x());
    }

    template<std::size_t N, Number T>
    constexpr Vec<N, T> Vec<N, T>::cross(const Vec& rhs) const noexcept requires (N == 3)
    {
        return Vec<N, T>
        {
            (this->y() * rhs.z()) - (this->z() * rhs.y()),
            (this->z() * rhs.x()) - (this->x() * rhs.z()),
            (this->x() * rhs.y()) - (this->y() * rhs.x())
        };
    }

    template<std::size_t N, Number T>
    [[nodiscard]] inline constexpr Vec<N, T> operator*(T scalar, const Vec<N, T>& v) noexcept
    {
        return v * scalar;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator+(const Vec<N, U>& rhs) const noexcept
    {
        Vec<N, U> out = *this;
        out += rhs;
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator-(const Vec<N, U>& rhs) const noexcept
    {
        Vec<N, U> out = *this;
        out -= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator*(const Vec<N, U>& rhs) const noexcept
    {
        Vec<N, U> out = *this;
        out *= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator/(const Vec<N, U>& rhs) const noexcept
    {
        Vec<N, U> out = *this;
        out /= rhs;
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator+(U scalar) const noexcept
    {
        Vec<N, U> out = *this;
        out += static_cast<T>(scalar);
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator-(U scalar) const noexcept
    {
        Vec<N, U> out = *this;
        out -= static_cast<T>(scalar);
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator*(U scalar) const noexcept
    {
        Vec<N, U> out = *this;
        out *= static_cast<T>(scalar);
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, U> Vec<N, T>::operator/(U scalar) const noexcept
    {
        Vec<N, U> out = *this;
        out /= static_cast<T>(scalar);
        return out;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, U>& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) += static_cast<T>(rhs.at(i));
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator-=(const Vec<N, U>& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) -= static_cast<T>(rhs.at(i));
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, U>& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) *= static_cast<T>(rhs.at(i));
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator/=(const Vec<N, U>& rhs) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) /= static_cast<T>(rhs.at(i));
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator+=(U scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) += static_cast<T>(scalar);
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator-=(U scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) -= static_cast<T>(scalar);
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator*=(U scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) *= static_cast<T>(scalar);
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T>& Vec<N, T>::operator/=(U scalar) noexcept
    {
        for (std::size_t i = 0; i < N; ++i) this->m_data.at(i) /= static_cast<T>(scalar);
        return *this;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator==(const Vec<N, U>& rhs) const noexcept
    {
        for (std::size_t i = 0; i < N; ++i) if (this->m_data.at(i) != static_cast<T>(rhs.at(i))) return false;
        return true;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator!=(const Vec<N, U>& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator<(const Vec<N, U>& rhs) const noexcept
    {
        return this->length_squared() < rhs.length_squared();
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator>(const Vec<N, U>& rhs) const noexcept
    {
        return this->length_squared() > rhs.length_squared();
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator<=(const Vec<N, U>& rhs) const noexcept
    {
        return this->length_squared() <= rhs.length_squared();
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr bool Vec<N, T>::operator>=(const Vec<N, U>& rhs) const noexcept
    {
        return this->length_squared() >= rhs.length_squared();
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr T Vec<N, T>::dot(const Vec<N, U>& rhs) const noexcept
    {
        T sum{};
        for (std::size_t i = 0; i < N; ++i) sum += this->m_data.at(i) * static_cast<T>(rhs.at(i));
        return sum;
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr T Vec<N, T>::distance(const Vec<N, U>& rhs) const noexcept
    {
        const Vec diff = *this - rhs;
        return std::sqrt(diff.length_squared());
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr T Vec<N, T>::cross(const Vec<N, U>& rhs) const noexcept requires (N == 2)
    {
        return (this->x() * static_cast<T>(rhs.y())) - (this->y() * static_cast<T>(rhs.x()));
    }

    template<std::size_t N, Number T>
    template<Number U> requires (std::is_convertible<U, T>::value)
    constexpr Vec<N, T> Vec<N, T>::cross(const Vec<N, U>& rhs) const noexcept requires (N == 3)
    {
        return Vec<N, T>
        {
            (this->y() * static_cast<T>(rhs.z())) - (this->z() * static_cast<T>(rhs.y())),
            (this->z() * static_cast<T>(rhs.x())) - (this->x() * static_cast<T>(rhs.z())),
            (this->x() * static_cast<T>(rhs.y())) - (this->y() * static_cast<T>(rhs.x()))
        };
    }

    template<std::size_t N, Number T, Number U>
    [[nodiscard]] inline constexpr Vec<N, T> operator*(T scalar, const Vec<N, U>& v) noexcept
    {
        return v * scalar;
    }
}

template<ikk::Number T>
class std::formatter<ikk::Vec2<T>>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Vec2<T>& vec, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "x: {}, y: {}", vec.x(), vec.y());
    }
};

template<ikk::Number T>
class std::formatter<ikk::Vec3<T>>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Vec3<T>& vec, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}", vec.x(), vec.y(), vec.z());
    }
};

template<ikk::Number T>
class std::formatter<ikk::Vec4<T>>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Vec4<T>& vec, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}, w: {}", vec.x(), vec.y(), vec.z(), vec.w());
    }
};