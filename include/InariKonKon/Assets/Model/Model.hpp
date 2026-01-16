#pragma once

#include <cstddef>
#include <cstring>
#include <vector>
#include <span>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

namespace ikk
{
    class [[nodiscard]] Model final
    {
    public:
        template<VertexType VertexType>
        [[nodiscard]] Model(const std::vector<VertexType>& vertices, const std::vector<std::uint32_t>& indices) noexcept;

        //TODO:
        //Load from file constructor...

        Model(const Model&) noexcept = default;
        Model(Model&&) noexcept = default;
        
        Model& operator=(const Model&) noexcept = default;
        Model& operator=(Model&&) noexcept = default;

        ~Model() noexcept = default;

        template<VertexType VertexType> requires (std::is_same<decltype(VertexType::color), Empty>::value == false)
        void setColor(const Color& color) noexcept;
        //TODO:
        //setVertices...

        template<VertexType VertexType>
        [[nodiscard]] const std::span<const VertexType> getVertexBuffer() const noexcept;
        template<VertexType VertexType>
        [[nodiscard]] const std::span<VertexType> getVertexBuffer() noexcept;

        [[nodiscard]] const std::vector<VertexAttribute>& getVertexAttributes() const noexcept;
        [[nodiscard]] const std::vector<std::byte>& getRawVertexBuffer() const noexcept;
        [[nodiscard]] const std::vector<std::uint32_t>& getIndices() const noexcept;
        [[nodiscard]] std::size_t getVertexStride() const noexcept;
    private:
        std::vector<std::byte> m_vertexBuffer = {};
        std::vector<std::uint32_t> m_indices = {};

        std::vector<VertexAttribute> m_vertexAttributes = {};
        std::size_t m_vertexStride = 0;

        mutable bool m_dirty = false;
        //TODO:
        //Remove.
        friend class OpenGL;
    };

    template<VertexType VertexType>
    Model::Model(const std::vector<VertexType>& vertices, const std::vector<std::uint32_t>& indices) noexcept
        : m_vertexStride(sizeof(VertexType)), m_indices(indices)
    {
        const std::size_t bufferSize = vertices.size() * this->m_vertexStride;
        this->m_vertexBuffer.resize(bufferSize);
        std::memcpy(this->m_vertexBuffer.data(), vertices.data(), bufferSize);

        const std::array<VertexAttribute, VertexType::getAttributeCount()>& attributes = VertexType::createAttributes();
        this->m_vertexAttributes = std::vector<VertexAttribute>{ attributes.begin(), attributes.end() };
    }

    template<VertexType VertexType> requires (std::is_same<decltype(VertexType::color), Empty>::value == false)
    void Model::setColor(const Color& color) noexcept
    {
        auto vertices = this->getVertexBuffer<VertexType>();
        for (VertexType& vertex : vertices)
            vertex.color = color;
        this->m_dirty = true;
    }

    template<VertexType VertexType>
    const std::span<const VertexType> Model::getVertexBuffer() const noexcept
    {
        return std::span<const VertexType>{reinterpret_cast<const VertexType*>(this->m_vertexBuffer.data()), this->m_vertexBuffer.size() / sizeof(VertexType)};
    }

    template<VertexType VertexType>
    const std::span<VertexType> Model::getVertexBuffer() noexcept
    {
        return std::span<VertexType>{reinterpret_cast<VertexType*>(this->m_vertexBuffer.data()), this->m_vertexBuffer.size() / sizeof(VertexType)};
    }
}