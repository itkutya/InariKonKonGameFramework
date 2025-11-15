#ifndef IKK_CAMERA_HPP
#define IKK_CAMERA_HPP

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"

namespace ikk
{
    class [[nodiscard]] Camera final : public Entity
    {
    public:
        enum struct Type : std::uint8_t
        {
            FPS, ThirdPerson
        };

        enum struct Projection : std::uint8_t
        {
            Perspective, Orthografic
        };

        [[nodiscard]] Camera(Type type, Vec3f position = {}, float pitch = 0.f, float yaw = 0.f, float nearPlane = 0.1f, float farPlane = 100.f) noexcept;

        Camera(const Camera& other) noexcept;
        Camera(Camera&& other) noexcept;

        Camera& operator=(const Camera& other) noexcept;
        Camera& operator=(Camera&& other) noexcept;

        ~Camera() noexcept;

        [[nodiscard]] const Transform3D& getTransform() const noexcept;
        [[nodiscard]] Transform3D& getTransform() noexcept;

        template<Projection P = Projection::Perspective> requires (P == Camera::Projection::Perspective)
        [[nodiscard]] const Mat4x4f getProjectionMatrix(float aspect) const noexcept;

        template<Projection P = Projection::Orthografic> requires (P == Camera::Projection::Orthografic)
        [[nodiscard]] const Mat4x4f getProjectionMatrix(float left, float right, float bottom, float top) const noexcept;

        [[nodiscard]] const Mat4x4f getViewMatrix() const noexcept;

        void processMouseEvent(const Vec2d& mousePos) noexcept;

        void enable(bool value = true) noexcept;
    private:
        bool m_enabled = true;
        Vec2d m_lastMousePosition{};

        float m_nearPlane = 0.1f;
        float m_farPlane = 100.f;

        float m_fov = 90.f;
        float m_zoom = 1.f;

        float m_horizontalSensitivity = 0.1f;
        float m_verticalSensitivity = 0.1f;

        Type m_type = Type::FPS;
    };

    template<Camera::Projection P> requires (P == Camera::Projection::Perspective)
    const Mat4x4f Camera::getProjectionMatrix(float aspect) const noexcept
    {
        if (isZero(aspect) == true || this->m_farPlane == this->m_nearPlane)
            return Mat4x4f::Identity();

        const float tanHalfFovy = std::tan(toRadian(Degree{ this->m_fov * this->m_zoom }).value / 2.f);

        Mat4x4f result{};
        result.at(0, 0) = 1.f / (aspect * tanHalfFovy);
        result.at(1, 1) = 1.f / tanHalfFovy;
        result.at(2, 2) = -(this->m_farPlane + this->m_nearPlane) / (this->m_farPlane - this->m_nearPlane);
        result.at(2, 3) = -(2.f * this->m_farPlane * this->m_nearPlane) / (this->m_farPlane - this->m_nearPlane);
        result.at(3, 2) = -1.f;
        result.at(3, 3) = 0.f;
        return result;
    }

    template<Camera::Projection P> requires (P == Camera::Projection::Orthografic)
    const Mat4x4f Camera::getProjectionMatrix(float left, float right, float bottom, float top) const noexcept
    {
        if (right == left || top == bottom || this->m_farPlane == this->m_nearPlane)
            return Mat4x4f::Identity();

        Mat4x4f result = Mat4x4f::Identity();
        result.at(0, 0) = 2.f / (right - left);
        result.at(1, 1) = 2.f / (top - bottom);
        result.at(2, 2) = -2.f / (this->m_farPlane - this->m_nearPlane);
        result.at(0, 3) = -(right + left) / (right - left);
        result.at(1, 3) = -(top + bottom) / (top - bottom);
        result.at(2, 3) = -(this->m_farPlane + this->m_nearPlane) / (this->m_farPlane - this->m_nearPlane);
        return result;
    }
}

#endif