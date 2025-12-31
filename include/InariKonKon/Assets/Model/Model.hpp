#ifndef IKK_MODEL_HPP
#define IKK_MODEL_HPP

#include <cstddef>
#include <cstring>
#include <vector>
#include <span>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp" // IWYU pragma: keep

namespace ikk
{
    //TODO:
    //Somehow fix this...
    class [[nodiscard]] Model final
    {
    public:
        //TODO:
        //Constrain types...
        template<class VertexType>
        [[nodiscard]] Model(const std::vector<VertexType>& vertices, const std::vector<std::uint32_t>& indices) noexcept;

        //TODO:
        //Load from file constructor...

        Model(const Model&) noexcept = default;
        Model(Model&&) noexcept = default;
        
        Model& operator=(const Model&) noexcept = default;
        Model& operator=(Model&&) noexcept = default;

        ~Model() noexcept = default;

        template<class VertexType>
        [[nodiscard]] const std::span<const VertexType> getVertexBuffer() const noexcept;

        template<class VertexType>
        [[nodiscard]] const std::span<VertexType> getVertexBuffer() noexcept;

        [[nodiscard]] const std::vector<VertexAttribute>& getVertexAttributes() const noexcept;
        [[nodiscard]] const std::vector<std::byte>& getRawVertexBuffer() const noexcept;
        [[nodiscard]] const std::vector<std::uint32_t>& getIndices() const noexcept;
        [[nodiscard]] std::size_t getVertexStride() const noexcept;
    private:
        std::vector<std::byte> m_vertexBuffer = {};
        std::size_t m_vertexStride = 0;
        std::vector<std::uint32_t> m_indices = {};

        std::vector<VertexAttribute> m_vertexAttributes = {};
    };

    template<class VertexType>
    Model::Model(const std::vector<VertexType>& vertices, const std::vector<std::uint32_t>& indices) noexcept
        : m_vertexStride(sizeof(VertexType)), m_indices(indices)
    {
        const std::size_t bufferSize = vertices.size() * this->m_vertexStride;
        this->m_vertexBuffer.resize(bufferSize);
        std::memcpy(this->m_vertexBuffer.data(), vertices.data(), bufferSize);

        const std::array<VertexAttribute, VertexType::getAttributeCount()>& attributes = VertexType::createAttributes();
        this->m_vertexAttributes = std::vector<VertexAttribute>{ attributes.begin(), attributes.end() };
    }

    template<class VertexType>
    const std::span<const VertexType> Model::getVertexBuffer() const noexcept
    {
        return std::span<const VertexType>{reinterpret_cast<const VertexType*>(this->m_vertexBuffer.data()), this->m_vertexBuffer.size() / sizeof(VertexType)};
    }

    template<class VertexType>
    const std::span<VertexType> Model::getVertexBuffer() noexcept
    {
        return std::span<VertexType>{reinterpret_cast<VertexType*>(this->m_vertexBuffer.data()), this->m_vertexBuffer.size() / sizeof(VertexType)};
    }
}

#endif