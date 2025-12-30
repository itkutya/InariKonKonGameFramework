#ifndef IKK_RECT_HPP
#define IKK_RECT_HPP

#include "InariKonKon/Math/Math.hpp"

namespace ikk
{
    //TODO:
    //Add inside & other functions...

    template<Number T>
    struct Rect
    {
        T left      = T{0};
        T top       = T{0};
        T width     = T{0};
        T height    = T{0};
    };

    using Rectf = Rect<float>;
    using Rectd = Rect<double>;
    using Recti = Rect<std::int32_t>;
    using RectI = Rect<std::int64_t>;
    using Rectu = Rect<std::uint32_t>;
    using RectU = Rect<std::uint64_t>;
}

#endif