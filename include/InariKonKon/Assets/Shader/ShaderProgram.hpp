#ifndef IKK_SHADER_PROGRAM_HPP
#define IKK_SHADER_PROGRAM_HPP

#include "InariKonKon/Assets/Shader/Shader.hpp"

namespace ikk
{
    class ShaderProgram : public ShaderBase
    {
    public:
        ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment) noexcept;

        ShaderProgram(const ShaderProgram& other) noexcept;
        ShaderProgram(ShaderProgram&&) noexcept = default;

        ShaderProgram& operator=(const ShaderProgram& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&&) noexcept = default;

        ~ShaderProgram() noexcept = default;
    protected:
        virtual void compile() noexcept override;
    private:
        const VertexShader* m_vertexShader = nullptr;
        const FragmentShader* m_fragmentShader = nullptr;
    };
}

#endif