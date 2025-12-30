#ifndef IKK_VERTEX_HPP
#define IKK_VERTEX_HPP

#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    template<typename T, typename... Ts>
    struct HasAttribute : std::disjunction<std::is_same<T, Ts>...> {};

    struct Empty{};

    //TODO:
    //Constrain types...
    template<class VecType, class... Attributes>
    struct [[nodiscard]] VertexBase
    {
        VecType position{};

        [[no_unique_address]] std::conditional_t<HasAttribute<Color, Attributes...>::value, Color, Empty> color{};
        [[no_unique_address]] std::conditional_t<HasAttribute<Vec2f, Attributes...>::value, Vec2f, Empty> texCoord{};
    };

    using UIVertex = VertexBase<Vec2f, Color>;
    using Vertex = VertexBase<Vec3f, Color>;
}

#endif