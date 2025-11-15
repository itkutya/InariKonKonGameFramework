#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"

#include "InariKonKon/Math/GlobalVectors.hpp"

namespace ikk
{
    Camera::Camera(Type type, Vec3f position, float pitch, float yaw, float nearPlane, float farPlane) noexcept
        : m_nearPlane(nearPlane), m_farPlane(farPlane), m_type(type)
    {
        this->addComponent(Transform3D{ position, RotationDegf{ pitch, yaw, 0.f } });
    }

    Camera::Camera(const Camera& other) noexcept
        : m_nearPlane(other.m_nearPlane), m_farPlane(other.m_farPlane), m_type(other.m_type)
    {
        Transform3D transform = other.getTransform();
        this->addComponent<Transform3D>(std::move(transform));
    }

    Camera::Camera(Camera&& other) noexcept
        : m_nearPlane(other.m_nearPlane), m_farPlane(other.m_farPlane), m_type(other.m_type)
    {
        Transform3D transform = other.getTransform();
        this->addComponent<Transform3D>(std::move(transform));
        other.removeComponent<Transform3D>();
    }

    Camera& Camera::operator=(const Camera& other) noexcept
    {
        if (this != &other)
        {
            this->m_nearPlane = other.m_nearPlane;
            this->m_farPlane  = other.m_farPlane;
            this->m_type      = other.m_type;

            Transform3D transform = other.getTransform();
            this->addComponent<Transform3D>(std::move(transform));
        }
        return *this;
    }

    Camera& Camera::operator=(Camera&& other) noexcept
    {
        if (this != &other)
        {
            this->m_nearPlane = other.m_nearPlane;
            this->m_farPlane  = other.m_farPlane;
            this->m_type      = other.m_type;

            Transform3D transform = other.getTransform();
            this->addComponent<Transform3D>(std::move(transform));
            other.removeComponent<Transform3D>();
        }
        return *this;
    }

    Camera::~Camera() noexcept
    {
        this->removeComponent<Transform3D>();
    }

    const Transform3D& Camera::getTransform() const noexcept
    {
        return *this->getComponent<Transform3D>().value();
    }

    Transform3D& Camera::getTransform() noexcept
    {
        return *this->getComponent<Transform3D>().value();
    }

    const Mat4x4f Camera::getViewMatrix() const noexcept
    {
        Mat4x4f view = this->getTransform().getWorldMatrix();
        view.inverse();
        return view;
    }

    void Camera::processMouseEvent(const Vec2d& mousePos) noexcept
    {
        if (this->m_enabled == false)
            return;

        const Vec2d diff = (this->m_lastMousePosition - mousePos);
        const Vec2f offset = Vec2f{ this->m_horizontalSensitivity, this->m_verticalSensitivity} * Vec2f{ (float)diff.x(), (float)diff.y() };
        this->m_lastMousePosition = mousePos;

        Transform3D& transform = this->getTransform();
        switch (this->m_type)
        {
        case Type::FPS:
        {
            transform.rotateGlobal(Degree{offset.x()}, worldUp);

            transform.rotateLocal(Degree{offset.y()}, {1.f, 0.f, 0.f});
            const float dotUp = transform.getForward().dot(worldUp);
            if (dotUp > 0.98f)
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});
            else if (dotUp < -0.98f)
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});

            transform.getLocalRotation().normalize();
        }
            break;
        case Type::ThirdPerson:
        {
            //TODO:
            float distance = 5.f;
            // Orbit camera around parent (target)
            // Yaw (horizontal) = rotate around world up
            transform.rotateGlobal(Degree{ offset.x() }, worldUp);

            // Pitch (vertical) = rotate around local right axis
            transform.rotateLocal(Degree{ offset.y() }, {1.f, 0.f, 0.f});

            // Clamp pitch to prevent flipping (optional)
            const float dotUp = transform.getForward().dot(worldUp);
            if (dotUp > 0.98f)  // looking almost straight down
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});
            else if (dotUp < -0.98f) // looking almost straight up
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});

            transform.getLocalRotation().normalize();

            // If camera has a parent (the target entity)
            if (Transform3D* parent = transform.m_parent; parent != nullptr)
            {
                // Get parent's world position
                const Vec3f targetPos = parent->getWorldPosition();

                // Desired camera position = target - forward * distance
                const Vec3f forward = transform.getForward();
                const Vec3f desiredPos = targetPos - (forward * distance);

                // Set camera position locally relative to parent
                Mat4x4f invParent = parent->getWorldMatrix();
                invParent.inverse();
                const Vec4f localPos4 = invParent * Vec4f{ desiredPos.x(), desiredPos.y(), desiredPos.z(), 1.0f };
                transform.getLocalPosition() = Vec3f{ localPos4.x(), localPos4.y(), localPos4.z() };
            }
        }
            break;
        }
    }

    void Camera::enable(bool value) noexcept
    {
        this->m_enabled = value;
    }
}