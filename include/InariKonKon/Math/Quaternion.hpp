#ifndef IKK_QUATERNION_HPP
#define IKK_QUATERNION_HPP

#include "InariKonKon/Math/Rotation.hpp"
#include "InariKonKon/Math/Mat.hpp"

namespace ikk
{
    template<std::floating_point T>
    struct [[nodiscard]] Quaternion final
    {
        [[nodiscard]] constexpr Quaternion() noexcept = default;
        [[nodiscard]] constexpr Quaternion(T x, T y, T z, T w) noexcept;
        [[nodiscard]] constexpr Quaternion(Vec3<T> vec, T w) noexcept;
        [[nodiscard]] constexpr Quaternion(RotationDeg<T> eulerDegrees) noexcept;
        [[nodiscard]] constexpr Quaternion(RotationRad<T> eulerRadians) noexcept;
        [[nodiscard]] constexpr Quaternion(Degree<T> degree, Vec3<T> axis) noexcept;
        [[nodiscard]] constexpr Quaternion(Radian<T> radian, Vec3<T> axis) noexcept;
        [[nodiscard]] constexpr Quaternion(Degree<T> degree, Vec2<T> axis) noexcept;
        [[nodiscard]] constexpr Quaternion(Radian<T> radian, Vec2<T> axis) noexcept;
        [[nodiscard]] constexpr Quaternion(const Mat3x3<T>& matrix) noexcept;
        [[nodiscard]] constexpr Quaternion(const Mat4x4<T>& matrix) noexcept;

        constexpr Quaternion(const Quaternion& other) noexcept = default;
        constexpr Quaternion(Quaternion&& other) noexcept = default;

        constexpr Quaternion& operator=(const Quaternion& other) noexcept = default;
        constexpr Quaternion& operator=(Quaternion&& other) noexcept = default;

        constexpr ~Quaternion() noexcept = default;

        [[nodiscard]] static constexpr Quaternion Identity() noexcept;

        [[nodiscard]] constexpr Quaternion operator+(const Quaternion& other) const noexcept;
        [[nodiscard]] constexpr Quaternion operator-(const Quaternion& other) const noexcept;
        [[nodiscard]] constexpr Quaternion operator*(const Quaternion& other) const noexcept;

        [[nodiscard]] constexpr Vec2<T> operator*(Vec2<T> vec) const noexcept;
        [[nodiscard]] constexpr Vec3<T> operator*(Vec3<T> vec) const noexcept;

        [[nodiscard]] constexpr Quaternion operator*(T scale) const noexcept;
        [[nodiscard]] constexpr Quaternion operator/(T scale) const noexcept;

        [[nodiscard]] constexpr Quaternion operator-() const noexcept;

        constexpr void operator+=(const Quaternion& other) noexcept;
        constexpr void operator-=(const Quaternion& other) noexcept;
        constexpr void operator*=(const Quaternion& other) noexcept;

        constexpr void operator*=(Vec2<T> vec) noexcept;
        constexpr void operator*=(Vec3<T> vec) noexcept;

        constexpr void operator*=(T scale) noexcept;
        constexpr void operator/=(T scale) noexcept;

        [[nodiscard]] constexpr bool operator==(const Quaternion& other) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Quaternion& other) const noexcept;

        constexpr void normalize() noexcept;

        [[nodiscard]] constexpr Quaternion getConjugate() const noexcept;

        [[nodiscard]] constexpr T length() const noexcept;

        [[nodiscard]] constexpr Mat3x3<T> toMat3x3() const noexcept;
        [[nodiscard]] constexpr Mat4x4<T> toMat4x4() const noexcept;

        T x{T{0}}, y{T{0}}, z{T{0}}, w{T{1}};
    };

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(T x, T y, T z, T w) noexcept
        : x(x), y(y), z(z), w(w)
    {}

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(Vec3<T> vec, T w) noexcept
        : Quaternion<T>(vec.x(), vec.y(), vec.z(), w)
    {}

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(RotationDeg<T> eulerDegrees) noexcept
        : Quaternion<T>(RotationRad<T>{ toRadian(eulerDegrees.yaw), toRadian(eulerDegrees.pitch), toRadian(eulerDegrees.roll) })
    {
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(RotationRad<T> eulerRadians) noexcept
    {
        const T halfYaw   = eulerRadians.yaw.value * T{0.5};
        const T halfPitch = eulerRadians.pitch.value * T{0.5};
        const T halfRoll  = eulerRadians.roll.value * T{0.5};

        const T sinPitch = std::sin(halfPitch);
        const T cosPitch = std::cos(halfPitch);
        const T sinYaw   = std::sin(halfYaw);
        const T cosYaw   = std::cos(halfYaw);
        const T sinRoll  = std::sin(halfRoll);
        const T cosRoll  = std::cos(halfRoll);

        this->x = cosYaw * sinPitch * cosRoll + sinYaw * cosPitch * sinRoll;
        this->y = sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll;
        this->z = cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll;
        this->w = cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll;

        this->normalize();
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(Degree<T> degree, Vec3<T> axis) noexcept
        : Quaternion<T>{toRadian(degree), axis}
    {
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(Radian<T> radian, Vec3<T> axis) noexcept
    {
        axis.normalize();
        const T halfAngle = radian.value / T{2};
        const T s = std::sin(halfAngle);
        
        this->x = axis.x() * s;
        this->y = axis.y() * s;
        this->z = axis.z() * s;
        this->w = std::cos(halfAngle);
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(Degree<T> degree, Vec2<T> axis) noexcept
        : Quaternion<T>{toRadian(degree), axis}
    {
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(Radian<T> radian, Vec2<T> axis) noexcept
    {
        axis.normalize();
        const T halfAngle = radian.value / T{2};
        const T s = std::sin(halfAngle);
        
        this->x = axis.x() * s;
        this->y = axis.y() * s;
        this->z = T{0};
        this->w = std::cos(halfAngle);
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(const Mat3x3<T>& matrix) noexcept
    {
        const T trace = matrix.at(0, 0) + matrix.at(1, 1) + matrix.at(2, 2);

        if (trace > T{0.0f}) 
        {
            const T s = std::sqrt(trace + T{1.0f}) * T{2.f};
            this->w = T{0.25f} * s;
            this->x = (matrix.at(2, 1) - matrix.at(1,2)) / s;
            this->y = (matrix.at(0, 2) - matrix.at(2,0)) / s;
            this->z = (matrix.at(1, 0) - matrix.at(0,1)) / s;
        }
        else if ((matrix.at(0, 0) > matrix.at(1, 1)) && (matrix.at(0, 0) > matrix.at(2, 2)))
        {
            const T s = std::sqrt(T{1.0f} + matrix.at(0, 0) - matrix.at(1, 1) - matrix.at(2, 2)) * T{2.f};
            this->w = (matrix.at(2, 1) - matrix.at(1, 2)) / s;
            this->x = T{0.25f} * s;
            this->y = (matrix.at(0, 1) + matrix.at(1, 0)) / s;
            this->z = (matrix.at(0, 2) + matrix.at(2, 0)) / s;
        } 
        else if (matrix.at(1, 1) > matrix.at(2, 2)) 
        {
            const T s = std::sqrt(T{1.0f} + matrix.at(1, 1) - matrix.at(0, 0) - matrix.at(2, 2)) * T{2.f};
            this->w = (matrix.at(0, 2) - matrix.at(2, 0)) / s;
            this->x = (matrix.at(0, 1) + matrix.at(1, 0)) / s;
            this->y = T{0.25f} * s;
            this->z = (matrix.at(1, 2) + matrix.at(2, 1)) / s;
        } 
        else 
        {
            const T s = std::sqrt(T{1.0f} + matrix.at(2, 2) - matrix.at(0, 0) - matrix.at(1, 1)) * T{2.f};
            this->w = (matrix.at(1, 0) - matrix.at(0, 1)) / s;
            this->x = (matrix.at(0, 2) + matrix.at(2, 0)) / s;
            this->y = (matrix.at(1, 2) + matrix.at(2, 1)) / s;
            this->z = T{0.25f} * s;
        }

        this->normalize();
    }

    template<std::floating_point T>
    constexpr Quaternion<T>::Quaternion(const Mat4x4<T>& matrix) noexcept
    : Quaternion<T>([&matrix]()
        {
            Mat3x3<T> temp{};
            temp.setColumn(0, { matrix.getColumn(0).x, matrix.getColumn(0).y, matrix.getColumn(0).z });
            temp.setColumn(1, { matrix.getColumn(1).x, matrix.getColumn(1).y, matrix.getColumn(1).z });
            temp.setColumn(2, { matrix.getColumn(2).x, matrix.getColumn(2).y, matrix.getColumn(2).z });

            return Quaternion<T>{ temp };
        })
    {
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::Identity() noexcept
    {
        static Quaternion<T> instance{T{0}, T{0}, T{0}, T{1}};
        return instance;
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>
        {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z,
            this->w + other.w
        };
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>
        {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z,
            this->w - other.w
        };
    }
    
    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>
        {
            this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
            this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
            this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w,
            this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z
        };
    }

    template<std::floating_point T>
    constexpr Vec2<T> Quaternion<T>::operator*(Vec2<T> vec) const noexcept
    {
        const Quaternion<T> qVec{ vec.x(), vec.y(), T{0}, T{0} };
        const Quaternion<T> qConj = this->getConjugate();
        const Quaternion<T> rotated = (*this) * qVec * qConj;
        return Vec2<T>{ rotated.x, rotated.y };
    }

    template<std::floating_point T>
    constexpr Vec3<T> Quaternion<T>::operator*(Vec3<T> vec) const noexcept
    {
        const Quaternion<T> qVec{ vec, T{0} };
        const Quaternion<T> qConj = this->getConjugate();
        const Quaternion<T> rotated = (*this) * qVec * qConj;
        return Vec3<T>{ rotated.x, rotated.y, rotated.z };
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator*(T scale) const noexcept
    {
        return Quaternion<T>
        {
            this->x * scale,
            this->y * scale,
            this->z * scale,
            this->w * scale
        };
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator/(T scale) const noexcept
    {
        return Quaternion<T>
        {
            this->x / scale,
            this->y / scale,
            this->z / scale,
            this->w / scale
        };
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::operator-() const noexcept
    {
        return Quaternion<T>
        {
            -this->x,
            -this->y,
            -this->z,
            -this->w
        };
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator+=(const Quaternion<T>& other) noexcept
    {
        *this = *this + other;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator-=(const Quaternion<T>& other) noexcept
    {
        *this = *this - other;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator*=(const Quaternion<T>& other) noexcept
    {
        *this = *this * other;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator*=(Vec2<T> vec) noexcept
    {
        *this = *this * vec;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator*=(Vec3<T> vec) noexcept
    {
        *this = *this * vec;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator*=(T scale) noexcept
    {
        *this = *this * scale;
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::operator/=(T scale) noexcept
    {
        *this = *this / scale;
    }

    template<std::floating_point T>
    constexpr bool Quaternion<T>::operator==(const Quaternion& other) const noexcept
    {
        return (isZero(this->x - other.x) == true &&
            isZero(this->y - other.y) == true &&
            isZero(this->z - other.z) == true &&
            isZero(this->w - other.w) == true);
    }

    template<std::floating_point T>
    constexpr bool Quaternion<T>::operator!=(const Quaternion& other) const noexcept
    {
        return !(*this == other);
    }

    template<std::floating_point T>
    constexpr Quaternion<T> Quaternion<T>::getConjugate() const noexcept
    {
        return Quaternion<T>{ -this->x, -this->y, -this->z, w };
    }

    template<std::floating_point T>
    constexpr T Quaternion<T>::length() const noexcept
    {
        return Vec4<T>{ this->x, this->y, this->z, this->w }.length();
    }

    template<std::floating_point T>
    constexpr void Quaternion<T>::normalize() noexcept
    {
        const T length = this->length();
        if (isZero(length) == false)
            (*this) /= length;
    }

    template<std::floating_point T>
    constexpr Mat3x3<T> Quaternion<T>::toMat3x3() const noexcept
    {
        const T xx = this->x * this->x, yy = this->y * this->y, zz = this->z * this->z;
        const T xy = this->x * this->y, xz = this->x * this->z, yz = this->y * this->z;
        const T wx = this->w * this->x, wy = this->w * this->y, wz = this->w * this->z;

        Mat3x3<T> m = Mat3x3<T>::Identity();

        m.at(0, 0) = T{1} - T{2} * (yy + zz);
        m.at(0, 1) = T{2} * (xy - wz);
        m.at(0, 2) = T{2} * (xz + wy);

        m.at(1, 0) = T{2} * (xy + wz);
        m.at(1, 1) = T{1} - T{2} * (xx + zz);
        m.at(1, 2) = T{2} * (yz - wx);

        m.at(2, 0) = T{2} * (xz - wy);
        m.at(2, 1) = T{2} * (yz + wx);
        m.at(2, 2) = T{1} - T{2} * (xx + yy);

        return m;
    }

    template<std::floating_point T>
    constexpr Mat4x4<T> Quaternion<T>::toMat4x4() const noexcept
    {
        const T xx = this->x * this->x, yy = this->y * this->y, zz = this->z * this->z;
        const T xy = this->x * this->y, xz = this->x * this->z, yz = this->y * this->z;
        const T wx = this->w * this->x, wy = this->w * this->y, wz = this->w * this->z;

        Mat4x4<T> m = Mat4x4<T>::Identity();

        m.at(0, 0) = T{1} - T{2} * (yy + zz);
        m.at(0, 1) = T{2} * (xy - wz);
        m.at(0, 2) = T{2} * (xz + wy);

        m.at(1, 0) = T{2} * (xy + wz);
        m.at(1, 1) = T{1} - T{2} * (xx + zz);
        m.at(1, 2) = T{2} * (yz - wx);

        m.at(2, 0) = T{2} * (xz - wy);
        m.at(2, 1) = T{2} * (yz + wx);
        m.at(2, 2) = T{1} - T{2} * (xx + yy);

        return m;
    }

    using Quaternionf = Quaternion<float>;
    using Quaterniond = Quaternion<double>;
}

#endif