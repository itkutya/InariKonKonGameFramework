#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp"
#include "InariKonKon/Utility/Utility.hpp"

namespace ikk
{
    ShaderProgram::ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment) noexcept
        : ShaderBase(Type::ShaderProgram, ""), m_vertexShader(&vertex), m_fragmentShader(&fragment)
    {
        this->compile();
    }

    ShaderProgram::ShaderProgram(const ShaderProgram& other) noexcept
        : ShaderBase(Type::ShaderProgram, "")
    {
        if (this != &other)
        {
            this->m_vertexShader = other.m_vertexShader;
            this->m_fragmentShader = other.m_fragmentShader;

            this->compile();
        }
    }

    ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other) noexcept
    {
        if (this != &other)
        {
            this->m_vertexShader = other.m_vertexShader;
            this->m_fragmentShader = other.m_fragmentShader;

            this->compile();
        }
        return *this;
    }

    void ShaderProgram::setUniform(std::string_view name, float value) const noexcept
    {
        this->activate();
        glCheck(glUniform1f(glGetUniformLocation(this->getID(), name.data()), value));
    }

    void ShaderProgram::setUniform(std::string_view name, double value) const noexcept
    {
        this->activate();
        glCheck(glUniform1d(glGetUniformLocation(this->getID(), name.data()), value));
    }

    void ShaderProgram::setUniform(std::string_view name, std::int32_t value) const noexcept
    {
        this->activate();
        glCheck(glUniform1i(glGetUniformLocation(this->getID(), name.data()), value));
    }

    void ShaderProgram::setUniform(std::string_view name, std::uint32_t value) const noexcept
    {
        this->activate();
        glCheck(glUniform1ui(glGetUniformLocation(this->getID(), name.data()), value));
    }

    void ShaderProgram::setUniform(std::string_view name, bool value) const noexcept
    {
        this->activate();
        glCheck(glUniform1i(glGetUniformLocation(this->getID(), name.data()), I32(value)));
    }

    void ShaderProgram::setUniform(std::string_view name, const Mat3x3f& value) const noexcept
    {
        this->activate();
        glCheck(glUniformMatrix3fv(glGetUniformLocation(this->getID(), name.data()),
            1, GL_TRUE, &value.at(0, 0)));
    }

    void ShaderProgram::setUniform(std::string_view name, const Mat4x4f& value) const noexcept
    {
        this->activate();
        glCheck(glUniformMatrix4fv(glGetUniformLocation(this->getID(), name.data()),
            1, GL_TRUE, &value.at(0, 0)));
    }

    void ShaderProgram::setUniform(std::string_view name, const Color& value) const noexcept
    {
        this->activate();
        const std::array<float, 4> array{ value.r, value.g, value.b, value.a };
        glCheck(glUniform4fv(glGetUniformLocation(this->getID(), name.data()), 1, array.data()));
    }

    void ShaderProgram::activate() const noexcept
    {
        glCheck(glUseProgram(this->getID()));
    }

    void ShaderProgram::compile() noexcept
    {
        this->getID() = glCreateProgram();
        if (this->getID() == 0)
        {
            DEBUG_LOG(Log::Level::Error, "Failed to create shader program object");
            return;
        }

        glCheck(glAttachShader(this->getID(), this->m_vertexShader->getID()));
        glCheck(glAttachShader(this->getID(), this->m_fragmentShader->getID()));
        glCheck(glLinkProgram(this->getID()));

        std::int32_t success = 0;
        glCheck(glGetProgramiv(this->getID(), GL_LINK_STATUS, &success));
        if (success == GL_FALSE)
        {
            char infoLog[1024] = {};
            glCheck(glGetProgramInfoLog(this->getID(), 1024, NULL, infoLog));
            DEBUG_LOG(Log::Level::Error, "Shader program linking failed:\n\tinfo: {}", infoLog);
            glCheck(glDeleteProgram(this->getID()));
        }
    }
}