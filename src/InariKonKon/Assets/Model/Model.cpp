#include "InariKonKon/Assets/Model/Model.hpp"

namespace ikk
{
    const std::vector<std::byte>& Model::getRawVertexBuffer() const noexcept
    {
        return this->m_vertexBuffer;
    }

    std::size_t Model::getVertexStride() const noexcept
    {
        return this->m_vertexStride;
    }

    const std::vector<std::uint32_t>& Model::getIndices() const noexcept
    {
        return this->m_indices;
    }
}