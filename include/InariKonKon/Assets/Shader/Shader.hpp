#pragma once

#include "InariKonKon/Assets/Shader/ShaderBase.hpp"

namespace ikk
{
    template<ShaderBase::Type T> requires (isValidShaderTypes(T))
    class [[nodiscard]] Shader final : public ShaderBase
    {
    public:
        [[nodiscard]] Shader(std::string_view source) noexcept;
        //[[nodiscard]] Shader(const File& source) noexcept;

        Shader(const Shader&) noexcept = default;
        Shader(Shader&&) noexcept = default;

        Shader& operator=(const Shader&) noexcept = default;
        Shader& operator=(Shader&&) noexcept = default;

        ~Shader() noexcept = default;
    private:
    };

    using VertexShader   = Shader<ShaderBase::Type::Vertex>;
    using FragmentShader = Shader<ShaderBase::Type::Fragment>;

    template<ShaderBase::Type T> requires (isValidShaderTypes(T))
    Shader<T>::Shader(std::string_view source) noexcept
        : ShaderBase(T, source)
    {
    }
}