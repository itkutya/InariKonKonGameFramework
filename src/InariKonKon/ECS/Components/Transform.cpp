#include "InariKonKon/ECS/Components/Transform.hpp"

#include <algorithm>

#include "InariKonKon/Math/GlobalVectors.hpp"

namespace ikk
{
    Transform<Dimension::_3D>::Transform(Vec3f position, RotationDegf rotation, Vec3f scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    Transform<Dimension::_3D>::Transform(Vec3f position, RotationRadf rotation, Vec3f scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    Transform<Dimension::_3D>::~Transform() noexcept
    {
        for (Transform* child : this->m_children)
            if (child != nullptr)
                child->m_parent = nullptr;
        this->m_children.clear();
    }

    const Mat4x4f Transform<Dimension::_3D>::getLocalMatrix() const noexcept
    {
        Mat4x4f translation = Mat4x4f::Identity();
        translation.setColumn(3, Vec4f{ this->m_localPosition.x(), this->m_localPosition.y(), this->m_localPosition.z(), 1.f });

        const Mat4x4f rotation = this->m_localRotation.toMat4x4();

        Mat4x4f scale = Mat4x4f::Identity();
        scale.at(0, 0) = this->m_localScale.x();
        scale.at(1, 1) = this->m_localScale.y();
        scale.at(2, 2) = this->m_localScale.z();

        return translation * rotation * scale;
    }

    const Mat4x4f Transform<Dimension::_3D>::getWorldMatrix() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldMatrix() * this->getLocalMatrix();
        else
            return this->getLocalMatrix();
    }

    const Vec3f& Transform<Dimension::_3D>::getLocalPosition() const noexcept
    {
        return this->m_localPosition;
    }

    const Quaternionf& Transform<Dimension::_3D>::getLocalRotation() const noexcept
    {
        return this->m_localRotation;
    }

    const Vec3f& Transform<Dimension::_3D>::getLocalScale() const noexcept
    {
        return this->m_localScale;
    }

    Vec3f& Transform<Dimension::_3D>::getLocalPosition() noexcept
    {
        return this->m_localPosition;
    }

    Quaternionf& Transform<Dimension::_3D>::getLocalRotation() noexcept
    {
        return this->m_localRotation;
    }

    Vec3f& Transform<Dimension::_3D>::getLocalScale() noexcept
    {
        return this->m_localScale;
    }

    const Vec3f Transform<Dimension::_3D>::getWorldPosition() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldPosition() + (this->m_parent->getWorldRotation() * (this->m_parent->getWorldScale() * this->m_localPosition));
        return this->m_localPosition;
    }

    const Quaternionf Transform<Dimension::_3D>::getWorldRotation() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldRotation() * this->m_localRotation;
        return this->m_localRotation;
    }

    const Vec3f Transform<Dimension::_3D>::getWorldScale() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldScale() * this->m_localScale;
        return this->m_localScale;
    }

    const Vec3f Transform<Dimension::_3D>::getRight() const noexcept
    {
        return this->getWorldRotation() * worldRight;
    }

    const Vec3f Transform<Dimension::_3D>::getUp() const noexcept
    {
        return this->getWorldRotation() * worldUp;
    }

    const Vec3f Transform<Dimension::_3D>::getForward() const noexcept
    {
        return this->getWorldRotation() * worldForward;
    }

    void Transform<Dimension::_3D>::translateLocal(Vec3f position) noexcept
    {
        this->m_localPosition += this->m_localRotation * position;
    }

    void Transform<Dimension::_3D>::translateGlobal(Vec3f position) noexcept
    {
        if (this->m_parent == nullptr)
        {
            this->m_localPosition += position;
            return;
        }

        Mat4x4f inv = this->m_parent->getWorldMatrix();
        inv.inverse();
        const Vec4f transformed = inv * Vec4f{ position.x(), position.y(), position.z(), 0.0f };
        this->m_localPosition += Vec3f{ transformed.x(), transformed.y(), transformed.z() };
    }

    void Transform<Dimension::_3D>::rotateLocal(Degree<float> degree, Vec3f direction) noexcept
    {
        this->rotateLocal(toRadian(degree), direction);
    }

    void Transform<Dimension::_3D>::rotateLocal(Radian<float> radian, Vec3f direction) noexcept
    {
        if (isZero(direction.length()))
            return;

        direction.normalize();
        this->m_localRotation = this->m_localRotation * Quaternionf{radian, direction};
        this->m_localRotation.normalize();
    }

    void Transform<Dimension::_3D>::rotateGlobal(Degree<float> degree, Vec3f axes) noexcept
    {
        this->rotateGlobal(toRadian(degree), axes);
    }

    void Transform<Dimension::_3D>::rotateGlobal(Radian<float> radian, Vec3f axes) noexcept
    {
        if (isZero(axes.length()))
            return;

        axes.normalize();
        this->m_localRotation = Quaternionf{radian, axes} * this->m_localRotation;
        this->m_localRotation.normalize();
    }

    void Transform<Dimension::_3D>::setLocalScale(Vec3f scale) noexcept
    {
        this->m_localScale = scale;
    }

    void Transform<Dimension::_3D>::setWorldScale(Vec3f scale) noexcept
    {
        if (this->m_parent != nullptr && isZero(this->m_parent->getWorldScale().length()) == false)
            this->m_localScale = scale / this->m_parent->getWorldScale();
        else
            this->m_localScale = scale;
    }

    void Transform<Dimension::_3D>::setParent(Transform& parent) noexcept
    {
        if (this->m_parent == &parent)
            return;

        if (this->m_parent != nullptr)
            std::erase(this->m_parent->m_children, this);

        this->m_parent = &parent;

        if (std::ranges::find(parent.m_children, this) == parent.m_children.end())
            parent.m_children.emplace_back(this);
    }

    void Transform<Dimension::_3D>::addChild(Transform& child) noexcept
    {
        if (std::ranges::find(this->m_children, &child) == this->m_children.end())
        {
            this->m_children.emplace_back(&child);
            child.m_parent = this;
        }
    }

    void Transform<Dimension::_3D>::removeChild(Transform& child) noexcept
    {
        if (auto it = std::ranges::find(this->m_children, &child); it != this->m_children.end())
        {
            (*it)->m_parent = nullptr;
            this->m_children.erase(it);
        }
    }
}