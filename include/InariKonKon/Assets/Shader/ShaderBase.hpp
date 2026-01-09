#ifndef IKK_SHADER_BASE_HPP
#define IKK_SHADER_BASE_HPP

#include <string_view>
#include <cstdint>
#include <string>

namespace ikk
{
    class [[nodiscard]] ShaderBase
    {
    public:
        //TODO:
        //Move this to Shader class if possible
        using IDType = std::uint32_t;

        //TODO:
        //Move this to Shader class if possible
        enum struct [[nodiscard]] Type : std::uint8_t
        {
            None,
            Vertex,
            Fragment,
            Geometry,
            Compute,
            ShaderProgram
        };

        ShaderBase(Type type, std::string_view source) noexcept;

        ShaderBase(const ShaderBase& other) noexcept;
        ShaderBase(ShaderBase&& other) noexcept;

        ShaderBase& operator=(const ShaderBase& other) noexcept;
        ShaderBase& operator=(ShaderBase&& other) noexcept;

        virtual ~ShaderBase() noexcept;

        [[nodiscard]] virtual const Type& getType() const noexcept final;
        [[nodiscard]] virtual const IDType& getID() const noexcept final;
        [[nodiscard]] virtual IDType& getID() noexcept final;

        [[nodiscard]] static constexpr std::string_view convertToString(Type type) noexcept;
    protected:
        virtual void compile() noexcept;
    private:
        Type m_type = Type::None;
        std::string m_source = {};
        IDType m_id = 0;

        void copy(const ShaderBase& other) noexcept;
        void move(ShaderBase&& other) noexcept;
    };

    static constexpr bool isValidShaderTypes(ShaderBase::Type T)
    {
        return (
            T == ShaderBase::Type::Vertex   ||
            T == ShaderBase::Type::Fragment ||
            T == ShaderBase::Type::Geometry ||
            T == ShaderBase::Type::Compute
                );
    }

    constexpr std::string_view ShaderBase::convertToString(Type type) noexcept
    {
        switch (type)
        {
            case Type::None:     return "None";
            case Type::Vertex:   return "Vertex";
            case Type::Fragment: return "Fragment";
            case Type::Geometry: return "Geometry";
            case Type::Compute:  return "Compute";
            case Type::ShaderProgram: return "ShaderProgram";
        }
    }
}

#endif