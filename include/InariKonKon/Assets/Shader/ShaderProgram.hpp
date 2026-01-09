#ifndef IKK_SHADER_PROGRAM_HPP
#define IKK_SHADER_PROGRAM_HPP

#include "InariKonKon/Assets/Shader/Shader.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Math/Mat.hpp"

namespace ikk
{
    class ShaderProgram final : public ShaderBase
    {
    public:
        ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment) noexcept;

        ShaderProgram(const ShaderProgram& other) noexcept;
        ShaderProgram(ShaderProgram&&) noexcept = default;

        ShaderProgram& operator=(const ShaderProgram& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&&) noexcept = default;

        ~ShaderProgram() noexcept = default;

        void setUniform(std::string_view name, float value) const noexcept;
        void setUniform(std::string_view name, double value) const noexcept;
        void setUniform(std::string_view name, std::int32_t value) const noexcept;
        void setUniform(std::string_view name, std::uint32_t value) const noexcept;
        void setUniform(std::string_view name, bool value) const noexcept;
        void setUniform(std::string_view name, const Mat3x3f& value) const noexcept;
        void setUniform(std::string_view name, const Mat4x4f& value) const noexcept;
        void setUniform(std::string_view name, const Color& value) const noexcept;

        void activate() const noexcept;
    protected:
        virtual void compile() noexcept final;
    private:
        const VertexShader* m_vertexShader = nullptr;
        const FragmentShader* m_fragmentShader = nullptr;
    };
}

#endif