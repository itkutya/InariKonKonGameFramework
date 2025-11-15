#ifndef IKK_MODEL_HPP
#define IKK_MODEL_HPP

#include <vector>

#include "InariKonKon/Vertex/Vertex.hpp"

namespace ikk
{
    struct [[nodiscard]] Model final
    {
        std::vector<Vertex> m_vertices = {};
        std::vector<std::uint32_t> m_indices = {};
    };

    //TODO:
    //basic objects like plane, triangle, square, etc...
}

#endif