#ifndef IKK_SHADER_HPP
#define IKK_SHADER_HPP

#include <string_view>
#include <cstdint>
#include <string>

namespace ikk
{
    class [[nodiscard]] Shader final
    {
    public:
        using IDType = std::uint32_t;

        enum struct [[nodiscard]] Type : std::uint8_t
        {
            Vertex,
            Fragment,
            Geometry,
            Compute
        };

        Shader(Type type, std::string_view source) noexcept;
        //[[nodiscard]] Shader(Type type, const File& source) noexcept;

        Shader(const Shader& other) noexcept;
        Shader(Shader&& other) noexcept;

        Shader& operator=(const Shader& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        ~Shader() noexcept;

        const Type& getType() const noexcept;
        const IDType& getID() const noexcept;

        static constexpr std::string_view convertToString(Type type) noexcept;
    private:
        Type m_type = Type::Vertex;
        std::string m_source = {};
        IDType m_id = 0;

        void compile() noexcept;

        void copy(const Shader& other) noexcept;
        void move(Shader&& other) noexcept;
    };

    constexpr std::string_view Shader::convertToString(Type type) noexcept
    {
        switch (type)
        {
            case Type::Vertex:   return "Vertex";
            case Type::Fragment: return "Fragment";
            case Type::Geometry: return "Geometry";
            case Type::Compute:  return "Compute";
        }
    }
}

#endif