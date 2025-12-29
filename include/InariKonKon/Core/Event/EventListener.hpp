#ifndef IKK_EVENT_LISTENER_HPP
#define IKK_EVENT_LISTENER_HPP

#include <algorithm>
#include <ranges> // IWYU pragma: keep
#include <vector>

#include "InariKonKon/Core/Event/Event.hpp"

namespace ikk
{
    template<EventSubType T>
    class EventListener
    {
    public:
        virtual ~EventListener() noexcept;

        virtual void onNotify(const T& event) noexcept = 0;

        virtual void add() noexcept final;
        virtual void remove() noexcept final;
    protected:
        EventListener(bool autoAdd = true) noexcept;

        EventListener(const EventListener&) noexcept = default;
        EventListener(EventListener&&) noexcept = default;

        EventListener& operator=(const EventListener&) noexcept = default;
        EventListener& operator=(EventListener&&) noexcept = default;
    private:
        inline static std::vector<EventListener<T>*> s_listeners;

        [[nodiscard]] static std::vector<EventListener<T>*>& getListeners() noexcept;

        friend Event;
    };

    template<EventSubType T>
    EventListener<T>::EventListener(bool autoAdd) noexcept
    {
        if (autoAdd)
            this->add();
        DEBUG_LOG({ "Event listener created" });
    }

    template<EventSubType T>
    EventListener<T>::~EventListener() noexcept
    {
        this->remove();
    }

    template<EventSubType T>
    void EventListener<T>::add() noexcept
    {
        if (const auto found = std::ranges::find(this, s_listeners); found != s_listeners.end())
            return;

        s_listeners.emplace_back(this);
        DEBUG_LOG({ "Event listener added" });
    }

    template<EventSubType T>
    void EventListener<T>::remove() noexcept
    {
        s_listeners.erase(std::ranges::find(s_listeners, this));
        DEBUG_LOG({ "Event listener removed" });
    }

    template<EventSubType T>
    std::vector<EventListener<T>*>& EventListener<T>::getListeners() noexcept
    {
        return s_listeners;
    }
}

#endif