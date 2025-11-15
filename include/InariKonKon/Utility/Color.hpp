#ifndef IKK_COLOR_HPP
#define IKK_COLOR_HPP

#include <format>

#include "InariKonKon/Utility/Clamped.hpp"

namespace ikk
{
    struct [[nodiscard]] Color final
    {
        struct [[nodiscard]] Channel final
        {
            [[nodiscard]] constexpr Channel() noexcept = default;

            [[nodiscard]] inline constexpr Channel(std::uint8_t value) noexcept
                : value(value / static_cast<float>(std::numeric_limits<std::uint8_t>::max()))
            {};
            
            [[nodiscard]] inline constexpr Channel(float value) noexcept
                : value(value)
            {};

            constexpr Channel(const Channel&) noexcept = default;
            constexpr Channel(Channel&&) noexcept = default;

            constexpr Channel& operator=(const Channel&) noexcept = default;
            constexpr Channel& operator=(Channel&&) noexcept = default;

            constexpr ~Channel() noexcept = default;

            [[nodiscard]] inline constexpr operator float() const noexcept
            {
                return value.value();
            }

            [[nodiscard]] inline constexpr std::uint8_t toUInt8() const noexcept
            {
                return static_cast<std::uint8_t>(value.value() * std::numeric_limits<std::uint8_t>::max());
            }

            Clamped<float, 0.f, 1.f> value = 0.f;
        };

        [[nodiscard]] constexpr Color() noexcept = default;

        [[nodiscard]] inline constexpr Color(Channel r, Channel g, Channel b, Channel a = { 1.f }) noexcept
            : r(r), g(g), b(b), a(a)
        {};

        [[nodiscard]] inline constexpr Color(std::uint32_t rgba) noexcept
            : r(static_cast<std::uint8_t>((rgba >> 24) & 0xFF)), g(static_cast<std::uint8_t>((rgba >> 16) & 0xFF)),
              b(static_cast<std::uint8_t>((rgba >> 8) & 0xFF)), a(static_cast<std::uint8_t>(rgba & 0xFF))
        {};

        constexpr Color(const Color&) noexcept = default;
        constexpr Color(Color&&) noexcept = default;

        constexpr Color& operator=(const Color&) noexcept = default;
        constexpr Color& operator=(Color&&) noexcept = default;

        constexpr ~Color() noexcept = default;

        [[nodiscard]] inline constexpr std::uint32_t toUInt32() const noexcept
        {
            return (static_cast<std::uint32_t>(r.toUInt8()) << 24) |
                   (static_cast<std::uint32_t>(g.toUInt8()) << 16) |
                   (static_cast<std::uint32_t>(b.toUInt8()) << 8)  |
                   (static_cast<std::uint32_t>(a.toUInt8()));
        }

        Channel r = {};
        Channel g = {};
        Channel b = {};
        Channel a = { 1.f };

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
    };

    inline constexpr Color Color::White             { 1.f, 1.f, 1.f, 1.f };
    inline constexpr Color Color::Black             { 0.f, 0.f, 0.f, 1.f };
    inline constexpr Color Color::Red               { 1.f, 0.f, 0.f, 1.f };
    inline constexpr Color Color::Green             { 0.f, 1.f, 0.f, 1.f };
    inline constexpr Color Color::Blue              { 0.f, 0.f, 1.f, 1.f };
    inline constexpr Color Color::Yellow            { 1.f, 1.f, 0.f, 1.f };
    inline constexpr Color Color::Magenta           { 1.f, 0.f, 1.f, 1.f };
    inline constexpr Color Color::Cyan              { 0.f, 1.f, 1.f, 1.f };
    inline constexpr Color Color::CornflowerBlue    { 0.392f, 0.584f, 0.929f, 1.f };
    inline constexpr Color Color::Transparent       { 0.f, 0.f, 0.f, 0.f };
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
        return std::format_to(ctx.out(), "{}", channel.value.value());
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