#include "InariKonKon/Assets/Shader/ShaderBase.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp"
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    ShaderBase::ShaderBase(Type type, std::string_view source) noexcept
        : m_type(type), m_source(source)
    {
        if (isValidShaderTypes(this->m_type) == true && this->m_source.empty() == false)
            this->compile();
    }

    ShaderBase::ShaderBase(const ShaderBase& other) noexcept
    {
        if (this != &other)
            this->copy(other);
    }

    ShaderBase::ShaderBase(ShaderBase&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
    }

    ShaderBase& ShaderBase::operator=(const ShaderBase& other) noexcept
    {
        if (this != &other)
            this->copy(other);
        return *this;
    }

    ShaderBase& ShaderBase::operator=(ShaderBase&& other) noexcept
    {
        if (this != &other)
            this->move(std::move(other));
        return *this;
    }

    ShaderBase::~ShaderBase() noexcept
    {
        if (this->m_id != 0)
            glCheck(glDeleteShader(this->m_id));
    }

    const ShaderBase::Type& ShaderBase::getType() const noexcept
    {
        return this->m_type;
    }

    const ShaderBase::IDType& ShaderBase::getID() const noexcept
    {
        return this->m_id;
    }

    ShaderBase::IDType& ShaderBase::getID() noexcept
    {
        return this->m_id;
    }

    void ShaderBase::compile() noexcept
    {
        constexpr auto convertToGLType = [](ShaderBase::Type type) noexcept
        {
            switch (type)
            {
                case ShaderBase::Type::None:            return 0;
                case ShaderBase::Type::Vertex:          return GL_VERTEX_SHADER;
                case ShaderBase::Type::Fragment:        return GL_FRAGMENT_SHADER;
                case ShaderBase::Type::Geometry:        return GL_GEOMETRY_SHADER;
                case ShaderBase::Type::Compute:         return GL_COMPUTE_SHADER;
                case ShaderBase::Type::ShaderProgram:   return 0;
            }
        };

        this->m_id = glCreateShader(convertToGLType(this->m_type));
        if (this->m_id == 0)
        {
            DEBUG_LOG(Log::Level::Error, "Failed to create shader object");
            return;
        }

        const char* src = this->m_source.c_str();
        glCheck(glShaderSource(this->m_id , 1, &src, NULL));
        glCheck(glCompileShader(this->m_id));

        std::int32_t success = 0;
        glCheck(glGetShaderiv(this->m_id, GL_COMPILE_STATUS, &success));
        if (success == GL_FALSE)
        {
            char infoLog[1024] = {};
            glCheck(glGetShaderInfoLog(this->m_id, 1024, NULL, infoLog));
            DEBUG_LOG(Log::Level::Error, "Shader compilation failed:\n\ttype: {}\n\tinfo: {}", this->convertToString(this->m_type), infoLog);
            glCheck(glDeleteShader(this->m_id));
        }
    }

    void ShaderBase::copy(const ShaderBase& other) noexcept
    {
        this->m_type = other.m_type;
        this->m_source = other.m_source;

        if (isValidShaderTypes(this->m_type) == true && this->m_source.empty() == false)
            this->compile();
    }

    void ShaderBase::move(ShaderBase&& other) noexcept
    {
        this->m_type = other.m_type;
        this->m_source = std::move(other.m_source);
        this->m_id = other.m_id;

        other.m_id = 0;
        other.m_type = Type::None;
        other.m_source = {};
    }
}