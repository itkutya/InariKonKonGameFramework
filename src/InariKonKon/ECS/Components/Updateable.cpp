#include "InariKonKon/ECS/Components/Updateable.hpp"

namespace ikk
{
    Updateable::Updateable(std::function<void()> callback) noexcept
        : m_callback(callback)
    {
    }

    void Updateable::update() noexcept
    {
        this->m_callback();
    }
}