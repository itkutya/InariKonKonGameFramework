#include "InariKonKon/Layer/Layer.hpp"

#include "InariKonKon/Application/Application.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    static Layer::ID getNextAvailableLayerID() noexcept
    {
        static Layer::ID s_nextID = 0;
        return ++s_nextID;
    }

    Layer::Layer() noexcept
        : m_id(getNextAvailableLayerID())
    {
        DEBUG_LOG("Layer created:\n\t{}", *this);
    }

    Layer::Layer(const Layer& other) noexcept
        : m_id(getNextAvailableLayerID())
    {
        this->attach(*other.m_app);
    }

    Layer::Layer(Layer&& other) noexcept
        : m_id(other.m_id)
    {
        this->attach(*other.m_app);

        other.detach();
        other.m_id = 0;
        other.m_app = nullptr;
    }

    Layer& Layer::operator=(const Layer& other) noexcept
    {
        if (this != &other)
        {
            this->m_id = getNextAvailableLayerID();
            this->attach(*other.m_app);
        }
        return *this;
    }

    Layer& Layer::operator=(Layer&& other) noexcept
    {
        if (this != &other)
        {
            this->m_id = other.m_id;
            this->attach(*other.m_app);

            other.detach();
            other.m_id = 0;
            other.m_app = nullptr;
        }
        return *this;
    }

    Layer::~Layer() noexcept
    {
        this->detach();
        DEBUG_LOG("Layer destroyed:\n\t{}", *this);
    }

    void Layer::attach(class Application& app) noexcept
    {
        if (this->m_app == &app)
            return;

        if (this->m_app != nullptr)
            this->detach();

        this->m_app = &app;
        this->m_app->m_layers.emplace_back(this);
        DEBUG_LOG("Layer attached to Application:\n\t{}\n\t{}", *this, app);
    }

    void Layer::detach() noexcept
    {
        if (this->m_app == nullptr)
            return;

        std::erase(this->m_app->m_layers, this);
        this->m_app = nullptr;
        DEBUG_LOG("Layer detached:\n\t{}", *this);
    }

    const Layer::ID& Layer::getID() const noexcept
    {
        return this->m_id;
    }
}