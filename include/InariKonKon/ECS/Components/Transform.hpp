#ifndef IKK_TRANSFORM_HPP
#define IKK_TRANSFORM_HPP

#include <vector>

#include "InariKonKon/Math/Quaternion.hpp"

namespace ikk
{
    //THIS ONE IS GOOD!!!
    template <Dimension D>
    struct TransformData;

    template <>
    struct TransformData<Dimension::_2D>
    {
        using PositionType = Vec2f;
    };

    template <>
    struct TransformData<Dimension::_3D>
    {
        using PositionType = Vec3f;
    };

    /*
    template<Dimension D>
    class Transform
    {
        TransformData<D>::PositionType position{};
    };
    */
    //OR
    template<Dimension D>
    class Transform;

    //TODO:
    template<>
    class [[nodiscard]] Transform<Dimension::_3D> final
    {
    public:
        [[nodiscard]] Transform() noexcept = default;
        [[nodiscard]] Transform(Vec3f position, RotationDegf rotation, Vec3f scale = Vec3f{ 1.f, 1.f, 1.f }) noexcept;
        [[nodiscard]] Transform(Vec3f position, RotationRadf rotation, Vec3f scale = Vec3f{ 1.f, 1.f, 1.f }) noexcept;

        //TODO:
        //These...
        Transform(const Transform& other) noexcept = default;
        Transform(Transform&& other) noexcept = default;

        Transform& operator=(const Transform& other) noexcept = default;
        Transform& operator=(Transform&& other) noexcept = default;

        ~Transform() noexcept;

        const Mat4x4f getLocalMatrix() const noexcept;
        const Mat4x4f getWorldMatrix() const noexcept;

        [[nodiscard]] const Vec3f& getLocalPosition() const noexcept;
        [[nodiscard]] const Quaternionf& getLocalRotation() const noexcept;
        [[nodiscard]] const Vec3f& getLocalScale() const noexcept;

        [[nodiscard]] Vec3f& getLocalPosition() noexcept;
        [[nodiscard]] Quaternionf& getLocalRotation() noexcept;
        [[nodiscard]] Vec3f& getLocalScale() noexcept;

        [[nodiscard]] const Vec3f getWorldPosition() const noexcept;
        [[nodiscard]] const Quaternionf getWorldRotation() const noexcept;
        [[nodiscard]] const Vec3f getWorldScale() const noexcept;

        [[nodiscard]] const Vec3f getRight() const noexcept;
        [[nodiscard]] const Vec3f getUp() const noexcept;
        [[nodiscard]] const Vec3f getForward() const noexcept;

        void translateLocal(Vec3f position) noexcept;
        void translateGlobal(Vec3f position) noexcept;

        void rotateLocal(Degree<float> degree, Vec3f direction) noexcept;
        void rotateLocal(Radian<float> radian, Vec3f direction) noexcept;
        void rotateGlobal(Degree<float> degree, Vec3f axes) noexcept;
        void rotateGlobal(Radian<float> radian, Vec3f axes) noexcept;

        void setLocalScale(Vec3f scale) noexcept;
        void setWorldScale(Vec3f scale) noexcept;

        void setParent(Transform& parent) noexcept;
        void addChild(Transform& child) noexcept;
        void removeChild(Transform& child) noexcept;
    private:
        Vec3f m_localPosition{ 0.f, 0.f, 0.f };
        Quaternionf m_localRotation = Quaternionf::Identity();
        Vec3f m_localScale{ 1.f, 1.f, 1.f };

        Transform* m_parent = nullptr;
        std::vector<Transform*> m_children{};

        friend class Camera;
    };

    //TODO:
    template<>
    class [[nodiscard]] Transform<Dimension::_2D> final
    {
    };

    //TODO:
    using Transform2D = Transform<Dimension::_2D>;
    using Transform3D = Transform<Dimension::_3D>;
}

#endif