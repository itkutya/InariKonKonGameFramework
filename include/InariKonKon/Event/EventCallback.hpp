#ifndef IKK_EVENT_CALLBACK_HPP
#define IKK_EVENT_CALLBACK_HPP

#include <type_traits>
#include <vector>

#include "InariKonKon/Utility/NonConstructible.hpp"
#include "InariKonKon/Event/Event.hpp"

namespace ikk
{
    template<class T, class E>
    concept EventCallbackType = std::is_invocable<T, E>::value && std::is_void<std::invoke_result_t<T, E>>::value;

    template<EventSubType E>
    class EventCallback : public NonConstructible
    {
    public:
        using CallbackFunc = void(*)(const E&);

        template<EventCallbackType<E> T>
        static void add(T callable) noexcept;
    private:
        inline static std::vector<CallbackFunc> s_eventCallabacks;

        [[nodiscard]] static const std::vector<CallbackFunc>& getCallbacks() noexcept;

        friend Event;
    };

    template<EventSubType E>
    template<EventCallbackType<E> T>
    void EventCallback<E>::add(T callable) noexcept
    {
        s_eventCallabacks.emplace_back(callable);
        DEBUG_LOG({ "Event callback created" });
    }

    template<EventSubType E>
    const std::vector<typename EventCallback<E>::CallbackFunc>& EventCallback<E>::getCallbacks() noexcept
    {
        return s_eventCallabacks;
    }
}

#endif