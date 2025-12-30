#ifndef IKK_COLOR_HPP
#define IKK_COLOR_HPP

#include <format>

#include "InariKonKon/Utility/Clamped.hpp"
#include "InariKonKon/Utility/Utility.hpp"

namespace ikk
{
    struct [[nodiscard]] Color final
    {
        struct [[nodiscard]] Channel final
        {
            [[nodiscard]] constexpr Channel() noexcept = default;
            [[nodiscard]] constexpr Channel(std::uint8_t value) noexcept;
            [[nodiscard]] constexpr Channel(Clamped<float, 0.f, 1.f> value) noexcept;

            constexpr Channel(const Channel&) noexcept = default;
            constexpr Channel(Channel&&) noexcept = default;

            constexpr Channel& operator=(const Channel&) noexcept = default;
            constexpr Channel& operator=(Channel&&) noexcept = default;

            constexpr ~Channel() noexcept = default;

            [[nodiscard]] constexpr operator float() const noexcept;
            [[nodiscard]] constexpr operator std::uint8_t() const noexcept;

            [[nodiscard]] constexpr float toFloat() const noexcept;
            [[nodiscard]] constexpr std::uint8_t toUInt8() const noexcept;

            std::uint8_t value = 0;
        };

        [[nodiscard]] constexpr Color() noexcept = default;
        [[nodiscard]] constexpr Color(Channel r, Channel g, Channel b, Channel a = { 0xff }) noexcept;
        [[nodiscard]] constexpr Color(std::uint32_t rgba) noexcept;

        constexpr Color(const Color&) noexcept = default;
        constexpr Color(Color&&) noexcept = default;

        constexpr Color& operator=(const Color&) noexcept = default;
        constexpr Color& operator=(Color&&) noexcept = default;

        constexpr ~Color() noexcept = default;

        [[nodiscard]] constexpr std::uint32_t toUInt32() const noexcept;

        Channel r = {};
        Channel g = {};
        Channel b = {};
        Channel a = { 0xff };

        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color CornflowerBlue;
        static const Color Transparent;

        static const Color Miku;
        static const Color Teto;
        static const Color Rin;
    };

    constexpr Color::Channel::Channel(std::uint8_t value) noexcept
        : value(value)
    {};

    constexpr Color::Channel::Channel(Clamped<float, 0.f, 1.f> value) noexcept
        : value(value.value() * std::numeric_limits<std::uint8_t>::max())
    {};

    constexpr Color::Channel::operator float() const noexcept
    {
        return this->toFloat();
    }

    constexpr Color::Channel::operator std::uint8_t() const noexcept
    {
        return this->toUInt8();
    }

    constexpr float Color::Channel::toFloat() const noexcept
    {
        return this->value / FLOAT(std::numeric_limits<std::uint8_t>::max());
    }

    constexpr std::uint8_t Color::Channel::toUInt8() const noexcept
    {
        return this->value;
    }

    constexpr Color::Color(Channel r, Channel g, Channel b, Channel a) noexcept
        : r(r), g(g), b(b), a(a)
    {};

    constexpr Color::Color(std::uint32_t rgba) noexcept
        : r(U8((rgba >> 24) & 0xFF)), g(U8((rgba >> 16) & 0xFF)), b(U8((rgba >> 8) & 0xFF)), a(U8(rgba & 0xFF))
    {};

    constexpr std::uint32_t Color::toUInt32() const noexcept
    {
        return (U32(r.toUInt8()) << 24) | (U32(g.toUInt8()) << 16) | (U32(b.toUInt8()) << 8)  | (U32(a.toUInt8()));
    }

    inline constexpr Color Color::White             { 0xff, 0xff, 0xff };
    inline constexpr Color Color::Black             { 0x00, 0x00, 0x00 };
    inline constexpr Color Color::Red               { 0xff, 0x00, 0x00 };
    inline constexpr Color Color::Green             { 0x00, 0xff, 0x00 };
    inline constexpr Color Color::Blue              { 0x00, 0x00, 0xff };
    inline constexpr Color Color::Yellow            { 0xff, 0xff, 0x00 };
    inline constexpr Color Color::Magenta           { 0xff, 0x00, 0xff };
    inline constexpr Color Color::Cyan              { 0x00, 0xff, 0xff };
    inline constexpr Color Color::CornflowerBlue    { NormalizedFloat{0.392f}, NormalizedFloat{0.584f}, NormalizedFloat{0.929f} };
    inline constexpr Color Color::Transparent       { 0x00, 0x00, 0x00, 0x00 };

    inline constexpr Color Color::Miku       { 0x39, 0xC5, 0xBB };
    inline constexpr Color Color::Teto       { 0xE3, 0x42, 0x34 };
    inline constexpr Color Color::Rin        { 0xFF, 0xD7, 0x00 };
}

template<>
class std::formatter<ikk::Color::Channel>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Color::Channel& channel, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "{}", channel.value);
    }
};

template<>
class std::formatter<ikk::Color>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::Color& color, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "r: {}\n\tg: {}\n\tb: {}\n\ta: {}", color.r, color.b, color.b, color.a);
    }
};

#endif