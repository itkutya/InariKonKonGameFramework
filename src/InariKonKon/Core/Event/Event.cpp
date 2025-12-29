#include "InariKonKon/Core/Event/Event.hpp"

#include "InariKonKon/Core/Event/EventListener.hpp"
#include "InariKonKon/Core/Event/EventCallback.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    void Event::dispatch() const noexcept
    {
        static const auto dispatchEvent = []<EventSubType T>(const T& event) noexcept
        {
            for (EventListener<T>* listener : EventListener<T>::getListeners())
            {
                listener->onNotify(event);
                DEBUG_LOG("Event ({:#x}) dispatched for listener(s) ({:#x}).",
                    reinterpret_cast<std::uintptr_t>(&event), reinterpret_cast<std::uintptr_t>(listener));
            }

            for (typename EventCallback<T>::CallbackFunc callback : EventCallback<T>::getCallbacks())
            {
                callback(event);
                DEBUG_LOG("Event ({:#x}) dispatched for callback(s) ({:#x}).",
                    reinterpret_cast<std::uintptr_t>(&event), reinterpret_cast<std::uintptr_t>(&callback));
            }
        };
        std::visit(dispatchEvent, this->m_data);
    }
}