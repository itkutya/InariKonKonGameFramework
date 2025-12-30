#include "InariKonKon/UI/UI.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"

namespace ikk
{
    UI::UI(Vec2f position, Vec2f size, Degreef rotation) noexcept
    {
        Transform2D transform{ position, {0.f, 0.f, rotation}, size };
        this->addComponent(std::move(transform));
    }

    UI::~UI() noexcept
    {
        this->removeComponent<Transform2D>();
    }
}