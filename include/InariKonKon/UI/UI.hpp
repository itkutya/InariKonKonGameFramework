#ifndef IKK_UI_HPP
#define IKK_UI_HPP

#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    class [[nodiscard]] UI : public Entity
    {
    public:
        virtual ~UI() noexcept;
    protected:
        [[nodiscard]] UI(Vec2f position, Vec2f size, Degreef rotation) noexcept;
        [[nodiscard]] UI(Vec2f position, Vec2f size, Radianf rotation) noexcept;

        UI(const UI&) noexcept = default;
        UI(UI&&) noexcept = default;

        UI& operator=(const UI&) noexcept = default;
        UI& operator=(UI&&) noexcept = default;
    private:
    };
}

#endif