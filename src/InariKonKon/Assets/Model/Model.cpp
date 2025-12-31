#include "InariKonKon/Assets/Model/Model.hpp"

namespace ikk
{
    const std::vector<VertexAttribute>& Model::getVertexAttributes() const noexcept
    {
        return this->m_vertexAttributes;
    }

    const std::vector<std::byte>& Model::getRawVertexBuffer() const noexcept
    {
        return this->m_vertexBuffer;
    }

    const std::vector<std::uint32_t>& Model::getIndices() const noexcept
    {
        return this->m_indices;
    }

    std::size_t Model::getVertexStride() const noexcept
    {
        return this->m_vertexStride;
    }
}