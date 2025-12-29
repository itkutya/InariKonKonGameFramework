#ifndef IKK_VERTEX_HPP
#define IKK_VERTEX_HPP

#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    struct Vertex final
    {
        Vec3f position = {};
        Color color = Color::White;
        Vec2f texCoord = {};
    };
}

#endif