#include "InariKonKon/UI/UI.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"

namespace ikk
{
    UI::UI(Vec2f position, Vec2f size, RotationDegf rotation) noexcept
    {
        //TODO:
        //Deal with the negative position
        Transform2D transform{ -position, rotation, size / 2.f };
        this->addComponent(std::move(transform));
    }

    UI::~UI() noexcept
    {
        this->removeComponent<Transform2D>();
    }
}