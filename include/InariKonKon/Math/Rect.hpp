#ifndef IKK_RECT_HPP
#define IKK_RECT_HPP

#include "InariKonKon/Math/Quaternion.hpp"
#include "InariKonKon/Math/Math.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    template<Number T>
    class [[nodiscard]] Rect final
    {
    public:
        [[nodiscard]] constexpr Rect() noexcept = default;
        [[nodiscard]] constexpr Rect(T left, T top, T width, T height) noexcept;
        [[nodiscard]] constexpr Rect(Vec2<T> position, Vec2<T> size) noexcept;
        [[nodiscard]] constexpr Rect(Vec4<T> vec) noexcept;

        constexpr Rect(const Rect&) noexcept = default;
        constexpr Rect(Rect&&) noexcept = default;

        constexpr Rect& operator=(const Rect&) noexcept = default;
        constexpr Rect& operator=(Rect&&) noexcept = default;

        constexpr ~Rect() noexcept = default;

        [[nodiscard]] constexpr const T& getLeft() const noexcept;
        [[nodiscard]] constexpr const T& getTop() const noexcept;
        [[nodiscard]] constexpr const T& getWidth() const noexcept;
        [[nodiscard]] constexpr const T& getHeight() const noexcept;

        [[nodiscard]] constexpr T getRight() const noexcept;
        [[nodiscard]] constexpr T getBottom() const noexcept;

        [[nodiscard]] constexpr T& getLeft() noexcept;
        [[nodiscard]] constexpr T& getTop() noexcept;
        [[nodiscard]] constexpr T& getWidth() noexcept;
        [[nodiscard]] constexpr T& getHeight() noexcept;

        template<Number U>
        [[nodiscard]] constexpr bool contains(Vec2<U> point) const noexcept;
        template<Number U>
        [[nodiscard]] constexpr bool contains(Vec2<U> point, Quaternionf rotation, Vec2f anchor = { 0.f, 0.f }) const noexcept;
    private:
        T m_left      = T{0};
        T m_top       = T{0};
        T m_width     = T{0};
        T m_height    = T{0};
    };

    using Rectf = Rect<float>;
    using Rectd = Rect<double>;
    using Recti = Rect<std::int32_t>;
    using RectI = Rect<std::int64_t>;
    using Rectu = Rect<std::uint32_t>;
    using RectU = Rect<std::uint64_t>;

    template<Number T>
    constexpr Rect<T>::Rect(T left, T top, T width, T height) noexcept
        : m_left(left), m_top(top), m_width(width), m_height(height)
    {}

    template<Number T>
    constexpr Rect<T>::Rect(Vec2<T> position, Vec2<T> size) noexcept
        : Rect(position.x(), position.y(), size.x(), size.y())
    {}

    template<Number T>
    constexpr Rect<T>::Rect(Vec4<T> vec) noexcept
        : Rect(vec.x(), vec.y(), vec.z(), vec.w())
    {}

    template<Number T>
    constexpr const T& Rect<T>::getLeft() const noexcept
    {
        return this->m_left;
    }

    template<Number T>
    constexpr const T& Rect<T>::getTop() const noexcept
    {
        return this->m_top;
    }

    template<Number T>
    constexpr const T& Rect<T>::getWidth() const noexcept
    {
        return this->m_width;
    }

    template<Number T>
    constexpr const T& Rect<T>::getHeight() const noexcept
    {
        return this->m_height;
    }

    template<Number T>
    constexpr T Rect<T>::getRight() const noexcept
    {
        return this->m_left + this->m_width;
    }

    template<Number T>
    constexpr T Rect<T>::getBottom() const noexcept
    {
        return this->m_top + this->m_height;
    }

    template<Number T>
    constexpr T& Rect<T>::getLeft() noexcept
    {
        return this->m_left;
    }

    template<Number T>
    constexpr T& Rect<T>::getTop() noexcept
    {
        return this->m_top;
    }

    template<Number T>
    constexpr T& Rect<T>::getWidth() noexcept
    {
        return this->m_width;
    }

    template<Number T>
    constexpr T& Rect<T>::getHeight() noexcept
    {
        return this->m_height;
    }

    template<Number T>
    template<Number U>
    constexpr bool Rect<T>::contains(Vec2<U> point) const noexcept
    {
        return  point.x() >= this->getLeft()    &&
                point.y() >= this->getTop()     &&
                point.x() <= this->getRight()   &&
                point.y() <= this->getBottom();
    }

    template<Number T>
    template<Number U>
    constexpr bool Rect<T>::contains(Vec2<U> point, Quaternionf rotation, Vec2f anchor) const noexcept
    {
        const Vec2<T> pivot =
        { 
            this->m_left + (this->m_width * anchor.x()), 
            this->m_top + (this->m_height * anchor.y()) 
        };

        const Vec2<T> d = point - pivot;

        const Vec2<T> localPoint = rotation.getConjugate() * d;

        const T minX = -this->m_width * static_cast<T>(anchor.x());
        const T maxX =  this->m_width * static_cast<T>((1.0f - anchor.x()));
        const T minY = -this->m_height * static_cast<T>(anchor.y());
        const T maxY =  this->m_height * static_cast<T>((1.0f - anchor.y()));

        return localPoint.x() >= minX && localPoint.x() <= maxX && localPoint.y() >= minY && localPoint.y() <= maxY;
    }
}

#endif