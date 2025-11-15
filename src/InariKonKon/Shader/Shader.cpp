#include "InariKonKon/Shader/Shader.hpp"

#include "glad/gl.h"

#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    inline static constexpr GLenum convertToGLType(Shader::Type type) noexcept
    {
        switch (type)
        {
            case Shader::Type::Vertex:   return GL_VERTEX_SHADER;
            case Shader::Type::Fragment: return GL_FRAGMENT_SHADER;
            case Shader::Type::Geometry: return GL_GEOMETRY_SHADER;
            case Shader::Type::Compute:  return GL_COMPUTE_SHADER;
        }
    }

    Shader::Shader(Type type, std::string_view source) noexcept
        : m_type(type), m_source(source)
    {
        this->compile();
    }

    Shader::Shader(const Shader& other) noexcept
    {
        if (this != &other)
            this->copy(other);
    }

    Shader::Shader(Shader&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
    }

    Shader& Shader::operator=(const Shader& other) noexcept
    {
        if (this != &other)
            this->copy(other);
        return *this;
    }
    
    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
        return *this;
    }

    Shader::~Shader() noexcept
    {
        if (this->m_id != 0)
            glDeleteShader(this->m_id);
    }

    const Shader::Type& Shader::getType() const noexcept
    {
        return this->m_type;
    }

    const Shader::IDType& Shader::getID() const noexcept
    {
        return this->m_id;
    }

    void Shader::compile() noexcept
    {
        this->m_id = glCreateShader(convertToGLType(this->m_type));
        const char* src = this->m_source.c_str();
        glShaderSource(this->m_id , 1, &src, NULL);
        glCompileShader(this->m_id);

        std::int32_t success = 0;
        glGetShaderiv(this->m_id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char infoLog[1024] = {};
            glGetShaderInfoLog(this->m_id, 1024, NULL, infoLog);
            DEBUG_LOG(Log::Level::Error, "Shader compilation failed:\n\ttype: {}\n\tinfo: {}", this->convertToString(this->m_type), infoLog);
            glDeleteShader(this->m_id);
        }
    }

    void Shader::copy(const Shader& other) noexcept
    {
        this->m_type = other.m_type;
        this->m_source = other.m_source;
        this->compile();
    }

    void Shader::move(Shader&& other) noexcept
    {
        this->m_type = other.m_type;
        this->m_source = std::move(other.m_source);
        this->m_id = other.m_id;

        other.m_id = 0;
        other.m_type = Type::Vertex;
        other.m_source = {};
    }
}