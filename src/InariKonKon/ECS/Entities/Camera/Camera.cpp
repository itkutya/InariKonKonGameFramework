#include "InariKonKon/ECS/Entities/Camera/Camera.hpp"

#include "InariKonKon/Math/GlobalVectors.hpp"

namespace ikk
{
    Camera::Camera(Type type, Vec3f position, float pitch, float yaw, float nearPlane, float farPlane) noexcept
        : m_nearPlane(nearPlane), m_farPlane(farPlane), m_type(type)
    {
        this->addComponent(Transform3D{ position, RotationDegf{ pitch, yaw, 0.f }});
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

    bool Camera::getState() const noexcept
    {
        return this->m_enabled;
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
        case Type::FirstPerson:
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
            
            transform.rotateGlobal(Degree{ offset.x() }, worldUp);
            transform.rotateLocal(Degree{ offset.y() }, {1.f, 0.f, 0.f});

            const float dotUp = transform.getForward().dot(worldUp);
            if (dotUp > 0.98f)
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});
            else if (dotUp < -0.98f)
                transform.rotateLocal(Degree{ -offset.y() }, {1.f, 0.f, 0.f});

            if (Transform3D* parent = transform.getParent(); parent != nullptr)
                transform.translateGlobal((parent->getWorldPosition() - (transform.getForward() * distance)) - transform.getWorldPosition());
        }
            break;
        case Type::None:
            break;
        }
    }

    void Camera::processMouseEvent(double delta) noexcept
    {
        if (this->m_enabled == false)
            return;

        if (this->m_canZoom == false)
            return;

        //TODO:
        //Clamp...
        this->m_zoom -= static_cast<float>(delta) * 0.1f;
    }

    void Camera::enable(bool value) noexcept
    {
        this->m_enabled = value;
    }
}