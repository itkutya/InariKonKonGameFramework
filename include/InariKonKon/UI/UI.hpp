#pragma once

#include "InariKonKon/ECS/Components/Transform.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"

namespace ikk
{
    class [[nodiscard]] UI : public Entity
    {
    public:
        struct Data
        {
            Vec2f position = {};
            Vec2f size = { 1.f, 1.f };
            Degreef rotation = {};
        };

        virtual ~UI() noexcept;

        [[nodiscard]] virtual const Transform2D& getTransform() const noexcept final;
        [[nodiscard]] virtual Transform2D& getTransform() noexcept final;

        virtual void setPosition(Vec2f position) noexcept final;
        virtual void setSize(Vec2f size) noexcept final;
        virtual void setRotation(RotationDegf rotation) noexcept final;
    protected:
        [[nodiscard]] UI(const Data& data) noexcept;

        UI(const UI&) noexcept = default;
        UI(UI&&) noexcept = default;

        UI& operator=(const UI&) noexcept = default;
        UI& operator=(UI&&) noexcept = default;
    private:
    };
}