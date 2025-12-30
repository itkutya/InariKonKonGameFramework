#ifndef IKK_TRANSFORM_HPP
#define IKK_TRANSFORM_HPP

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/ECS/Entities/Hierarchy.hpp"
#include "InariKonKon/Math/GlobalVectors.hpp"
#include "InariKonKon/Math/Quaternion.hpp"

namespace ikk
{
    template<Dimension D>
    struct TransformData;

    template<>
    struct TransformData<Dimension::_2D> final : public NonConstructible
    {
        using VecType = Vec2f;
        using MatType = Mat3x3f;
    
        using PositionType = Vec2f;
        using RotationType = Quaternionf;
        using ScaleType = Vec2f;
    };

    template<>
    struct TransformData<Dimension::_3D> final : public NonConstructible
    {
        using VecType = Vec3f;
        using MatType = Mat4x4f;

        using PositionType = Vec3f;
        using RotationType = Quaternionf;
        using ScaleType = Vec3f;
    };

    template<Dimension D>
    class [[nodiscard]] Transform final : public Hierarchy<Transform<D>>
    {
    public:
        using VecType = TransformData<D>::VecType;
        using MatType = TransformData<D>::MatType;

        using PositionType = TransformData<D>::PositionType;
        using RotationType = TransformData<D>::RotationType;
        using ScaleType = TransformData<D>::ScaleType;

        [[nodiscard]] Transform() noexcept = default;
        [[nodiscard]] Transform(PositionType position, RotationDegf rotation, ScaleType scale = ScaleType(1.f)) noexcept;
        [[nodiscard]] Transform(PositionType position, RotationRadf rotation = {}, ScaleType scale = ScaleType(1.f)) noexcept;

        Transform(const Transform&) noexcept = default;
        Transform(Transform&&) noexcept = default;

        Transform& operator=(const Transform&) noexcept = default;
        Transform& operator=(Transform&&) noexcept = default;

        ~Transform() noexcept = default;

        const MatType getLocalMatrix() const noexcept;
        const MatType getWorldMatrix() const noexcept;

        [[nodiscard]] const PositionType& getLocalPosition() const noexcept;
        [[nodiscard]] const RotationType& getLocalRotation() const noexcept;
        [[nodiscard]] const ScaleType& getLocalScale() const noexcept;

        [[nodiscard]] PositionType& getLocalPosition() noexcept;
        [[nodiscard]] RotationType& getLocalRotation() noexcept;
        [[nodiscard]] ScaleType& getLocalScale() noexcept;

        [[nodiscard]] const PositionType getWorldPosition() const noexcept;
        [[nodiscard]] const RotationType getWorldRotation() const noexcept;
        [[nodiscard]] const ScaleType getWorldScale() const noexcept;

        [[nodiscard]] const VecType getRight() const noexcept;
        [[nodiscard]] const VecType getUp() const noexcept;
        [[nodiscard]] const VecType getForward() const noexcept;

        void translate(PositionType position) noexcept;
        void translateLocal(PositionType position) noexcept;
        void translateGlobal(PositionType position) noexcept;

        void rotateLocal(Degree<float> degree, VecType direction) noexcept requires(D == Dimension::_3D);
        void rotateLocal(Radian<float> radian, VecType direction) noexcept requires(D == Dimension::_3D);
        void rotateGlobal(Degree<float> degree, VecType axes) noexcept requires(D == Dimension::_3D);
        void rotateGlobal(Radian<float> radian, VecType axes) noexcept requires(D == Dimension::_3D);

        void rotateLocal(Degree<float> degree) noexcept requires(D == Dimension::_2D);
        void rotateLocal(Radian<float> radian) noexcept requires(D == Dimension::_2D);
        void rotateGlobal(Degree<float> degree) noexcept requires(D == Dimension::_2D);
        void rotateGlobal(Radian<float> radian) noexcept requires(D == Dimension::_2D);

        void setLocalScale(ScaleType scale) noexcept;
        void setWorldScale(ScaleType scale) noexcept;
    private:
        PositionType m_localPosition = PositionType(0.f);
        RotationType m_localRotation = RotationType();
        ScaleType m_localScale = ScaleType(1.f);

        mutable bool m_dirty = true;
        mutable MatType m_localMatrix = MatType::Identity();
        mutable MatType m_worldMatrix = MatType::Identity();

        void recalculateMatricies() const noexcept;
    };

    using Transform2D = Transform<Dimension::_2D>;
    using Transform3D = Transform<Dimension::_3D>;

    template<Dimension D>
    Transform<D>::Transform(PositionType position, RotationDegf rotation, ScaleType scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    template<Dimension D>
    Transform<D>::Transform(PositionType position, RotationRadf rotation, ScaleType scale) noexcept
        : m_localPosition(position), m_localRotation(rotation), m_localScale(scale)
    {
    }

    template<Dimension D>
    const Transform<D>::MatType Transform<D>::getLocalMatrix() const noexcept
    {
        if (this->m_dirty == true)
            this->recalculateMatricies();
        return this->m_localMatrix;
    }

    template<Dimension D>
    const Transform<D>::MatType Transform<D>::getWorldMatrix() const noexcept
    {
        if (this->m_dirty == true)
            this->recalculateMatricies();
        return this->m_worldMatrix;
    }

    template<Dimension D>
    const Transform<D>::PositionType& Transform<D>::getLocalPosition() const noexcept
    {
        return this->m_localPosition;
    }

    template<Dimension D>
    const Transform<D>::RotationType& Transform<D>::getLocalRotation() const noexcept
    {
        return this->m_localRotation;
    }

    template<Dimension D>
    const Transform<D>::ScaleType& Transform<D>::getLocalScale() const noexcept
    {
        return this->m_localScale;
    }

    template<Dimension D>
    Transform<D>::PositionType& Transform<D>::getLocalPosition() noexcept
    {
        return this->m_localPosition;
    }

    template<Dimension D>
    Transform<D>::RotationType& Transform<D>::getLocalRotation() noexcept
    {
        return this->m_localRotation;
    }

    template<Dimension D>
    Transform<D>::ScaleType& Transform<D>::getLocalScale() noexcept
    {
        return this->m_localScale;
    }

    template<Dimension D>
    const Transform<D>::PositionType Transform<D>::getWorldPosition() const noexcept
    {
        if (this->getParent() != nullptr)
            return this->getParent()->getWorldPosition() + (this->getParent()->getWorldRotation() * (this->getParent()->getWorldScale() * this->m_localPosition));
        return this->m_localPosition;
    }

    template<Dimension D>
    const Transform<D>::RotationType Transform<D>::getWorldRotation() const noexcept
    {
        if (this->getParent() != nullptr)
            return this->getParent()->getWorldRotation() * this->m_localRotation;
        return this->m_localRotation;
    }

    template<Dimension D>
    const Transform<D>::ScaleType Transform<D>::getWorldScale() const noexcept
    {
        if (this->getParent() != nullptr)
            return this->getParent()->getWorldScale() * this->m_localScale;
        return this->m_localScale;
    }

    template<Dimension D>
    const Transform<D>::VecType Transform<D>::getRight() const noexcept
    {
        return this->getWorldRotation() * worldRight;
    }

    template<Dimension D>
    const Transform<D>::VecType Transform<D>::getUp() const noexcept
    {
        return this->getWorldRotation() * worldUp;
    }

    template<Dimension D>
    const Transform<D>::VecType Transform<D>::getForward() const noexcept
    {
        return this->getWorldRotation() * worldForward;
    }

    template<Dimension D>
    void Transform<D>::translate(PositionType position) noexcept
    {
        this->m_localPosition += position;
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::translateLocal(Transform<D>::PositionType position) noexcept
    {
        this->m_localPosition += (this->m_localRotation * position);
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::translateGlobal(Transform<D>::PositionType position) noexcept
    {
        if (this->getParent() != nullptr)
        {
            Transform<D>::MatType inv = this->getParent()->getWorldMatrix();
            inv.inverse();
            if constexpr (D == Dimension::_2D)
            {
                const Vec3f transformed = inv * Vec3f{ position.x(), position.y(), 0.0f };
                this->m_localPosition += Vec2f{ transformed.x(), transformed.y() };
            }
            else
            {
                const Vec4f transformed = inv * Vec4f{ position.x(), position.y(), position.z(), 0.0f };
                this->m_localPosition += Vec3f{ transformed.x(), transformed.y(), transformed.z() };
            }
            this->m_dirty = true;
        }
        else
            this->translateLocal(position);
    }

    template<Dimension D>
    void Transform<D>::rotateLocal(Degree<float> degree, Transform<D>::VecType direction) noexcept requires(D == Dimension::_3D)
    {
        this->rotateLocal(toRadian(degree), direction);
    }

    template<Dimension D>
    void Transform<D>::rotateLocal(Radian<float> radian, Transform<D>::VecType direction) noexcept requires(D == Dimension::_3D)
    {
        if (isZero(direction.length()))
            return;

        direction.normalize();
        this->m_localRotation = this->m_localRotation * Quaternionf{radian, direction};
        this->m_localRotation.normalize();
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Degree<float> degree, Transform<D>::VecType axes) noexcept requires(D == Dimension::_3D)
    {
        this->rotateGlobal(toRadian(degree), axes);
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Radian<float> radian, Transform<D>::VecType axes) noexcept requires(D == Dimension::_3D)
    {
        if (isZero(axes.length()))
            return;

        axes.normalize();
        this->m_localRotation = Quaternionf{radian, axes} * this->m_localRotation;
        this->m_localRotation.normalize();
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::rotateLocal(Degree<float> degree) noexcept requires(D == Dimension::_2D)
    {
        this->rotateLocal(toRadian(degree));
    }

    template<Dimension D>
    void Transform<D>::rotateLocal(Radian<float> radian) noexcept requires(D == Dimension::_2D)
    {
        this->m_localRotation = this->m_localRotation * Quaternionf{radian, Vec3f::Z()};
        this->m_localRotation.normalize();
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Degree<float> degree) noexcept requires(D == Dimension::_2D)
    {
        this->rotateGlobal(toRadian(degree));
    }

    template<Dimension D>
    void Transform<D>::rotateGlobal(Radian<float> radian) noexcept requires(D == Dimension::_2D)
    {
        this->m_localRotation = Quaternionf{radian, Vec3f::Z()} * this->m_localRotation;
        this->m_localRotation.normalize();
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::setLocalScale(Transform<D>::ScaleType scale) noexcept
    {
        this->m_localScale = scale;
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::setWorldScale(Transform<D>::ScaleType scale) noexcept
    {
        if (this->getParent() != nullptr && isZero(this->getParent()->getWorldScale().length()) == false)
            this->m_localScale = scale / this->getParent()->getWorldScale();
        else
            this->m_localScale = scale;
        this->m_dirty = true;
    }

    template<Dimension D>
    void Transform<D>::recalculateMatricies() const noexcept
    {
        Transform<D>::MatType translation = Transform<D>::MatType::Identity();
        Transform<D>::MatType rotation = Transform<D>::MatType::Identity();
        Transform<D>::MatType scale = Transform<D>::MatType::Identity();

        if constexpr (D == Dimension::_2D)
        {
            translation.setColumn(2, Vec3f{ this->m_localPosition.x(), this->m_localPosition.y(), 1.f });

            rotation = this->m_localRotation.toMat3x3();

            scale.at(0, 0) = this->m_localScale.x();
            scale.at(1, 1) = this->m_localScale.y();
        }
        else
        {
            translation.setColumn(3, Vec4f{ this->m_localPosition.x(), this->m_localPosition.y(), this->m_localPosition.z(), 1.f });

            rotation = this->m_localRotation.toMat4x4();

            scale.at(0, 0) = this->m_localScale.x();
            scale.at(1, 1) = this->m_localScale.y();
            scale.at(2, 2) = this->m_localScale.z();
        }

        this->m_localMatrix = translation * rotation * scale;

        if (this->getParent() != nullptr)
            this->m_worldMatrix = this->getParent()->getWorldMatrix() * this->m_localMatrix;
        else
            this->m_worldMatrix = this->m_localMatrix;

        this->m_dirty = false;
    }
}

#endif