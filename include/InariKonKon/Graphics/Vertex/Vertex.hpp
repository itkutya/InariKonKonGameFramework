#pragma once

#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    struct VertexAttribute
    {
        enum struct Type : std::uint8_t
        {
            Float, Double, Int8, UInt8, Int16, UInt16, Int32, UInt32
        };

        std::size_t count = 0;
        Type type = Type::Float;
        bool normalized = false;
        std::size_t offset = 0;
    };

    struct Empty{};

    struct TextureCoord
    {
        Clamped<float, 0.f, 1.f> x = 0.f;
        Clamped<float, 0.f, 1.f> y = 0.f;
    };

    template<class T>
    concept VecType = requires { typename T::Type; } && std::is_arithmetic<typename T::Type>::value;

    template<class T>
    concept VertexAttributeType = std::same_as<T, Color> || std::same_as<T, TextureCoord>;

    template<class... Ts>
    struct UniqueAttributes : std::true_type {};

    template<class T, class... Ts>
    struct UniqueAttributes<T, Ts...> : std::bool_constant<(!std::same_as<T, Ts> && ...) && UniqueAttributes<Ts...>::value> {};

    template<VertexAttributeType T, VertexAttributeType... Ts>
    struct HasAttribute : std::disjunction<std::is_same<T, Ts>...> {};

    template<VecType VecType, VertexAttributeType... Attributes> requires UniqueAttributes<Attributes...>::value
    struct [[nodiscard]] VertexBase
    {
        VecType position{};

        [[no_unique_address]] std::conditional<HasAttribute<Color, Attributes...>::value, Color, Empty>::type color{};
        [[no_unique_address]] std::conditional<HasAttribute<TextureCoord, Attributes...>::value, TextureCoord, Empty>::type texCoord{};

        static constexpr std::size_t getAttributeCount() noexcept;
        static constexpr std::size_t getStride() noexcept;

        static constexpr std::array<VertexAttribute, getAttributeCount()> createAttributes() noexcept;
    };

    using UIVertex = VertexBase<Vec2f, Color, TextureCoord>;
    using Vertex = VertexBase<Vec3f, Color, TextureCoord>;

    template<VecType VecType, VertexAttributeType... Attributes> requires UniqueAttributes<Attributes...>::value
    constexpr std::size_t VertexBase<VecType, Attributes...>::getAttributeCount() noexcept
    {
        return 1 + (HasAttribute<Color, Attributes...>::value == true ? 1 : 0) + (HasAttribute<TextureCoord, Attributes...>::value == true ? 1 : 0);
    }

    template<VecType VecType, VertexAttributeType... Attributes> requires UniqueAttributes<Attributes...>::value
    constexpr std::size_t VertexBase<VecType, Attributes...>::getStride() noexcept
    {
        return sizeof(VertexBase<VecType, Attributes...>);
    }

    template<class T>
    struct isVertex : std::false_type {};

    template<VecType VecType, VertexAttributeType... Attributes>
    struct isVertex<VertexBase<VecType, Attributes...>> : std::true_type {};

    template<class T>
    concept VertexType = isVertex<std::remove_cvref_t<T>>::value;

    template<>
    constexpr std::array<VertexAttribute, UIVertex::getAttributeCount()> UIVertex::createAttributes() noexcept
    {
        using VertexType = UIVertex;
        std::array<VertexAttribute, getAttributeCount()> attributes{};

        attributes.at(0).count = 2;
        attributes.at(0).type = VertexAttribute::Type::Float;
        attributes.at(0).normalized = false;
        attributes.at(0).offset = offsetof(VertexType, position);
        
        attributes.at(1).count = 4;
        attributes.at(1).type = VertexAttribute::Type::UInt8;
        attributes.at(1).normalized = true;
        attributes.at(1).offset = offsetof(VertexType, color);

        attributes.at(2).count = 2;
        attributes.at(2).type = VertexAttribute::Type::Float;
        attributes.at(2).normalized = false;
        attributes.at(2).offset = offsetof(VertexType, texCoord);

        return attributes;
    }

    template<>
    constexpr std::array<VertexAttribute, Vertex::getAttributeCount()> Vertex::createAttributes() noexcept
    {
        using VertexType = Vertex;
        std::array<VertexAttribute, getAttributeCount()> attributes{};

        attributes.at(0).count = 3;
        attributes.at(0).type = VertexAttribute::Type::Float;
        attributes.at(0).normalized = 0;
        attributes.at(0).offset = offsetof(VertexType, position);
        
        attributes.at(1).count = 4;
        attributes.at(1).type = VertexAttribute::Type::UInt8;
        attributes.at(1).normalized = false;
        attributes.at(1).offset = offsetof(VertexType, color);

        attributes.at(2).count = 2;
        attributes.at(2).type = VertexAttribute::Type::Float;
        attributes.at(2).normalized = false;
        attributes.at(2).offset = offsetof(VertexType, texCoord);

        return attributes;
    }
}