#ifndef IKK_VERTEX_HPP
#define IKK_VERTEX_HPP

#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    template<typename T, typename... Ts>
    struct HasAttribute : std::disjunction<std::is_same<T, Ts>...> {};

    struct Empty{};

    struct VertexAttribute
    {
        enum struct Type : std::uint8_t
        {
        };

        std::size_t count = 0;
        //TODO:
        //Own types and then in the renderer convert them...
        std::size_t type = 0;
        bool normalized = false;
        void* offset = nullptr;
    };

    //TODO:
    //Constrain types...
    template<class VecType, class... Attributes>
    struct [[nodiscard]] VertexBase
    {
        VecType position{};

        [[no_unique_address]] std::conditional_t<HasAttribute<Color, Attributes...>::value, Color, Empty> color{};
        [[no_unique_address]] std::conditional_t<HasAttribute<Vec2f, Attributes...>::value, Vec2f, Empty> texCoord{};

        static constexpr std::size_t getAttributeCount() noexcept
        {
            return 1 + (HasAttribute<Color, Attributes...>::value ? 1 : 0) + (HasAttribute<Vec2f, Attributes...>::value ? 1 : 0);
        }

        static constexpr std::size_t getStride() noexcept
        {
            return sizeof(VertexBase<VecType, Attributes...>);
        }

        static constexpr std::array<VertexAttribute, getAttributeCount()> createAttributes() noexcept;
    };

    using UIVertex = VertexBase<Vec2f, Color>;
    using Vertex = VertexBase<Vec3f, Color>;

    template<>
    constexpr std::array<VertexAttribute, UIVertex::getAttributeCount()> UIVertex::createAttributes() noexcept
    {
        std::array<VertexAttribute, getAttributeCount()> attributes{};

        attributes.at(0).count = 2;
        attributes.at(0).type = 0x1406; //GL_FLOAT
        attributes.at(0).normalized = 0;
        attributes.at(0).offset = (void*)(offsetof(UIVertex, position));
        
        attributes.at(1).count = 4;
        attributes.at(1).type = 0x1401; //GL_UNSIGNED_BYTE
        attributes.at(1).normalized = 1;
        attributes.at(1).offset = (void*)(offsetof(UIVertex, color));

        return attributes;
    }

    template<>
    constexpr std::array<VertexAttribute, Vertex::getAttributeCount()> Vertex::createAttributes() noexcept
    {
        std::array<VertexAttribute, getAttributeCount()> attributes{};

        attributes.at(0).count = 3;
        attributes.at(0).type = 0x1406; //GL_FLOAT
        attributes.at(0).normalized = 0;
        attributes.at(0).offset = (void*)(offsetof(UIVertex, position));
        
        attributes.at(1).count = 4;
        attributes.at(1).type = 0x1401; //GL_UNSIGNED_BYTE
        attributes.at(1).normalized = 1;
        attributes.at(1).offset = (void*)(offsetof(UIVertex, color));

        return attributes;
    }
}

#endif