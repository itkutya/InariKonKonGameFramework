#ifndef IKK_INARIKONKON_HPP
#define IKK_INARIKONKON_HPP

#include "InariKonKon/Core/Application/Application.hpp"  // IWYU pragma: keep
#include "InariKonKon/Core/Event/EventListener.hpp"      // IWYU pragma: keep
#include "InariKonKon/Core/Event/EventCallback.hpp"      // IWYU pragma: keep

namespace ikk
{
    struct ___
    {
        [[nodiscard]] static bool init();
    };
}

#define INARIKONKON_ENSURE_INIT if (ikk::___::init() == false) return -1

#endif