#include "InariKonKon/Assets/Shader/ShaderProgram.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp"

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