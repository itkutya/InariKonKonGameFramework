#ifndef IKK_TRANSFORM_HPP
#define IKK_TRANSFORM_HPP

#include <vector>

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Math/GlobalVectors.hpp"
#include "InariKonKon/Math/Quaternion.hpp"

namespace ikk
{
    template <Dimension D>
    struct TransformData;

    template <>
    struct TransformData<Dimension::_2D> final : public NonConstructible
    {
        using VecType = Vec2f;
        using MatType = Mat3x3f;
    
        using PositionType = Vec2f;
        using RotationType = Quaternionf;
        using ScaleType = Vec2f;
    };

    template <>
    struct TransformData<Dimension::_3D> final : public NonConstructible
    {
        using VecType = Vec3f;
        using MatType = Mat4x4f;

        using PositionType = Vec3f;
        using RotationType = Quaternionf;
        using ScaleType = Vec3f;
    };

    template<Dimension D>
    class [[nodiscard]] Transform final
    {
    public:
        [[nodiscard]] Transform() noexcept = default;
        [[nodiscard]] Transform(TransformData<D>::PositionType position, RotationDegf rotation, TransformData<D>::ScaleType scale = typename TransformData<D>::ScaleType(1.f)) noexcept;
        [[nodiscard]] Transform(TransformData<D>::PositionType position, RotationRadf rotation, TransformData<D>::ScaleType scale = typename TransformData<D>::ScaleType(1.f)) noexcept;

        //TODO:
        //These...
        Transform(const Transform& other) noexcept = default;
        Transform(Transform&& other) noexcept = default;

        Transform& operator=(const Transform& other) noexcept = default;
        Transform& operator=(Transform&& other) noexcept = default;

        ~Transform() noexcept;

        const TransformData<D>::MatType getLocalMatrix() const noexcept;
        const TransformData<D>::MatType getWorldMatrix() const noexcept;

        [[nodiscard]] const TransformData<D>::PositionType& getLocalPosition() const noexcept;
        [[nodiscard]] const TransformData<D>::RotationType& getLocalRotation() const noexcept;
        [[nodiscard]] const TransformData<D>::ScaleType& getLocalScale() const noexcept;

        [[nodiscard]] TransformData<D>::PositionType& getLocalPosition() noexcept;
        [[nodiscard]] TransformData<D>::RotationType& getLocalRotation() noexcept;
        [[nodiscard]] TransformData<D>::ScaleType& getLocalScale() noexcept;

        [[nodiscard]] const TransformData<D>::PositionType getWorldPosition() const noexcept;
        [[nodiscard]] const TransformData<D>::RotationType getWorldRotation() const noexcept;
        [[nodiscard]] const TransformData<D>::ScaleType getWorldScale() const noexcept;

        [[nodiscard]] const TransformData<D>::VecType getRight() const noexcept;
        [[nodiscard]] const TransformData<D>::VecType getUp() const noexcept;
        [[nodiscard]] const TransformData<D>::VecType getForward() const noexcept;

        void translateLocal(TransformData<D>::PositionType position) noexcept;
        void translateGlobal(TransformData<D>::PositionType position) noexcept;

        void rotateLocal(Degree<float> degree, TransformData<D>::VecType direction) noexcept;
        void rotateLocal(Radian<float> radian, TransformData<D>::VecType direction) noexcept;
        void rotateGlobal(Degree<float> degree, TransformData<D>::VecType axes) noexcept;
        void rotateGlobal(Radian<float> radian, TransformData<D>::VecType axes) noexcept;

        void setLocalScale(TransformData<D>::ScaleType scale) noexcept;
        void setWorldScale(TransformData<D>::ScaleType scale) noexcept;

        const Transform* getParent() const noexcept;
        Transform* getParent() noexcept;

        const std::vector<Transform*>& getChildren() const noexcept;
        std::vector<Transform*>& getChildren() noexcept;

        void setParent(Transform& parent) noexcept;
        void addChild(Transform& child) noexcept;
        void removeChild(Transform& child) noexcept;
    private:
        TransformData<D>::PositionType m_localPosition{};
        TransformData<D>::RotationType m_localRotation{};
        TransformData<D>::ScaleType m_localScale{};

        Transform* m_parent = nullptr;
        std::vector<Transform*> m_children{};
    };

    template<Dimension D>
    Transform<D>::Transform(TransformData<D>::PositionType position, RotationDegf rotation, TransformData<D>::ScaleType scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    template<Dimension D>
    Transform<D>::Transform(TransformData<D>::PositionType position, RotationRadf rotation, TransformData<D>::ScaleType scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    template<Dimension D>
    Transform<D>::~Transform() noexcept
    {
        for (Transform* child : this->m_children)
            if (child != nullptr)
                child->m_parent = nullptr;
        this->m_children.clear();
    }

    template<Dimension D>
    const TransformData<D>::MatType Transform<D>::getLocalMatrix() const noexcept
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

    template<Dimension D>
    const TransformData<D>::MatType Transform<D>::getWorldMatrix() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldMatrix() * this->getLocalMatrix();
        else
            return this->getLocalMatrix();
    }

    template<Dimension D>
    const TransformData<D>::PositionType& Transform<D>::getLocalPosition() const noexcept
    {
        return this->m_localPosition;
    }

    template<Dimension D>
    const TransformData<D>::RotationType& Transform<D>::getLocalRotation() const noexcept
    {
        return this->m_localRotation;
    }

    template<Dimension D>
    const TransformData<D>::ScaleType& Transform<D>::getLocalScale() const noexcept
    {
        return this->m_localScale;
    }

    template<Dimension D>
    TransformData<D>::PositionType& Transform<D>::getLocalPosition() noexcept
    {
        return this->m_localPosition;
    }

    template<Dimension D>
    TransformData<D>::RotationType& Transform<D>::getLocalRotation() noexcept
    {
        return this->m_localRotation;
    }

    template<Dimension D>
    TransformData<D>::ScaleType& Transform<D>::getLocalScale() noexcept
    {
        return this->m_localScale;
    }

    template<Dimension D>
    const TransformData<D>::PositionType Transform<D>::getWorldPosition() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldPosition() + (this->m_parent->getWorldRotation() * (this->m_parent->getWorldScale() * this->m_localPosition));
        return this->m_localPosition;
    }

    template<Dimension D>
    const TransformData<D>::RotationType Transform<D>::getWorldRotation() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldRotation() * this->m_localRotation;
        return this->m_localRotation;
    }

    template<Dimension D>
    const TransformData<D>::ScaleType Transform<D>::getWorldScale() const noexcept
    {
        if (this->m_parent != nullptr)
            return this->m_parent->getWorldScale() * this->m_localScale;
        return this->m_localScale;
    }

    template<Dimension D>
    const TransformData<D>::VecType Transform<D>::getRight() const noexcept
    {
        return this->getWorldRotation() * worldRight;
    }

    template<Dimension D>
    const TransformData<D>::VecType Transform<D>::getUp() const noexcept
    {
        return this->getWorldRotation() * worldUp;
    }

    template<Dimension D>
    const TransformData<D>::VecType Transform<D>::getForward() const noexcept
    {
        return this->getWorldRotation() * worldForward;
    }

    template<Dimension D>
    void Transform<D>::translateLocal(TransformData<D>::PositionType position) noexcept
    {
        this->m_localPosition += this->m_localRotation * position;
    }

    template<Dimension D>
    void Transform<D>::translateGlobal(TransformData<D>::PositionType position) noexcept
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

    template<Dimension D>
    void Transform<D>::rotateLocal(Degree<float> degree, TransformData<D>::VecType direction) noexcept
    {
        this->rotateLocal(toRadian(degree), direction);
    }

    template<Dimension D>
    void Transform<D>::rotateLocal(Radian<float> radian, TransformData<D>::VecType direction) noexcept
    {
        if (isZero(direction.length()))
            return;

        direction.normalize();
        this->m_localRotation = this->m_localRotation * Quaternionf{radian, direction};
        this->m_localRotation.normalize();
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Degree<float> degree, TransformData<D>::VecType axes) noexcept
    {
        this->rotateGlobal(toRadian(degree), axes);
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Radian<float> radian, TransformData<D>::VecType axes) noexcept
    {
        if (isZero(axes.length()))
            return;

        axes.normalize();
        this->m_localRotation = Quaternionf{radian, axes} * this->m_localRotation;
        this->m_localRotation.normalize();
    }

    template<Dimension D>
    void Transform<D>::setLocalScale(TransformData<D>::ScaleType scale) noexcept
    {
        this->m_localScale = scale;
    }

    template<Dimension D>
    void Transform<D>::setWorldScale(TransformData<D>::ScaleType scale) noexcept
    {
        if (this->m_parent != nullptr && isZero(this->m_parent->getWorldScale().length()) == false)
            this->m_localScale = scale / this->m_parent->getWorldScale();
        else
            this->m_localScale = scale;
    }

    template<Dimension D>
    const Transform<D>* Transform<D>::getParent() const noexcept
    {
        return this->m_parent;
    }

    template<Dimension D>
    Transform<D>* Transform<D>::getParent() noexcept
    {
        return this->m_parent;
    }

    template<Dimension D>
    const std::vector<Transform<D>*>& Transform<D>::getChildren() const noexcept
    {
        return this->m_children;
    }

    template<Dimension D>
    std::vector<Transform<D>*>& Transform<D>::getChildren() noexcept
    {
        return this->m_children;
    }

    template<Dimension D>
    void Transform<D>::setParent(Transform& parent) noexcept
    {
        if (this->m_parent == &parent)
            return;

        if (this->m_parent != nullptr)
            std::erase(this->m_parent->m_children, this);

        this->m_parent = &parent;

        if (std::ranges::find(parent.m_children, this) == parent.m_children.end())
            parent.m_children.emplace_back(this);
    }

    template<Dimension D>
    void Transform<D>::addChild(Transform& child) noexcept
    {
        if (std::ranges::find(this->m_children, &child) == this->m_children.end())
        {
            this->m_children.emplace_back(&child);
            child.m_parent = this;
        }
    }

    template<Dimension D>
    void Transform<D>::removeChild(Transform& child) noexcept
    {
        if (auto it = std::ranges::find(this->m_children, &child); it != this->m_children.end())
        {
            (*it)->m_parent = nullptr;
            this->m_children.erase(it);
        }
    }

    using Transform2D = Transform<Dimension::_2D>;
    using Transform3D = Transform<Dimension::_3D>;
}

#endif