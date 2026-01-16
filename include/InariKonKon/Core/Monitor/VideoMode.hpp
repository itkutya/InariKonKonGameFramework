#pragma once

#include <cstdint>
#include <format>

namespace ikk
{
    struct [[nodiscard]] VideoMode
    {
        std::uint8_t redBits = 0;
        std::uint8_t greenBits = 0;
        std::uint8_t blueBits = 0;
        
        std::uint16_t width = 0;
        std::uint16_t height = 0;
        std::uint16_t refreshRate = 0;
    };
}

template<>
class std::formatter<ikk::VideoMode>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) noexcept
    {
        return ctx.begin();
    }

    constexpr auto format(const ikk::VideoMode& videomode, std::format_context& ctx) const noexcept
    {
        return std::format_to(ctx.out(), "width: {}\n\theight: {}\n\trefresh rate: {}\n\tr: {}\n\tg: {}\n\tb: {}",
            videomode.width, videomode.height, videomode.refreshRate, videomode.redBits, videomode.greenBits, videomode.blueBits);
    }
};