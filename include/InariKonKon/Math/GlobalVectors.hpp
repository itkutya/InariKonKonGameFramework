#ifndef IKK_GLOBAL_VECTORS
#define IKK_GLOBAL_VECTORS

#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    inline static constexpr const Vec3f worldRight   = Vec3f::X();
    inline static constexpr const Vec3f worldUp      = Vec3f::Y();
    inline static constexpr const Vec3f worldForward = -Vec3f::Z();
}

#endif