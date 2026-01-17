#include "InariKonKon/UI/UI.hpp"

#include "InariKonKon/ECS/Components/Transform.hpp"

namespace ikk
{
    UI::UI(const Data& data) noexcept
    {
        this->addComponent(Transform2D{ data.position, { 0.f, 0.f, data.rotation }, data.size });
    }

    UI::~UI() noexcept
    {
        this->removeComponent<Transform2D>();
    }

    const Transform2D& UI::getTransform() const noexcept
    {
        return *this->getComponent<Transform2D>().value();
    }

    Transform2D& UI::getTransform() noexcept
    {
        return *this->getComponent<Transform2D>().value();
    }

    void UI::setPosition(Vec2f position) noexcept
    {
        //TODO:
    }

    void UI::setSize(Vec2f size) noexcept
    {
        this->getTransform().setWorldScale(size);
    }

    void UI::setRotation(RotationDegf rotation) noexcept
    {
        //TODO:
    }
}