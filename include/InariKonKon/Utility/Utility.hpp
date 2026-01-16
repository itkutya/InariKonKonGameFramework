#pragma once

#include <concepts>
#include <cstdint>
#include <string>

namespace ikk
{
    #ifdef NDEBUG
        #define IKK_RELEASE
    #else
        #define IKK_DEBUG
    #endif

    #define DEFINE_CAST_FUNC(NAME, TYPE)                                            \
    template<class T> requires std::convertible_to<T, TYPE>                         \
    [[nodiscard]] inline constexpr TYPE NAME(T value) noexcept { return static_cast<TYPE>(value); }

    DEFINE_CAST_FUNC(U64, std::uint64_t)
    DEFINE_CAST_FUNC(U32, std::uint32_t)
    DEFINE_CAST_FUNC(U16, std::uint16_t)
    DEFINE_CAST_FUNC(U8,  std::uint8_t)

    DEFINE_CAST_FUNC(I64, std::int64_t)
    DEFINE_CAST_FUNC(I32, std::int32_t)
    DEFINE_CAST_FUNC(I16, std::int16_t)
    DEFINE_CAST_FUNC(I8,  std::int8_t)

    DEFINE_CAST_FUNC(F32, float)
    DEFINE_CAST_FUNC(F64, double)

    DEFINE_CAST_FUNC(BOOL, bool)

    inline constexpr const char8_t* TO_UTF8(const char* x) noexcept { return reinterpret_cast<const char8_t*>(x); }
    inline constexpr const char* TO_ANSI(const char8_t* x) noexcept { return reinterpret_cast<const char*>(x); }

    [[nodiscard]] inline constexpr const std::u8string convertUnicodeToUTF8(const std::string& string) noexcept
    {
        std::u8string result;
        for (const char& c : string)
        {
            if (c <= 0x7F)
                result.push_back(static_cast<char8_t>(c));
            else
            {
                result.push_back(static_cast<char8_t>(0xC0 | (c >> 6)));
                result.push_back(static_cast<char8_t>(0x80 | (c & 0x3F)));
            }
        }
        return result;
    }

    [[nodiscard]] inline constexpr const std::string convertUTF8ToUnicode(const std::u8string& string) noexcept
    {
        std::string result;
        std::size_t i = 0;
        while (i < string.size())
        {
            const char8_t byte = string.at(i);
            if ((byte & 0x80) == 0)
            {
                result.push_back(static_cast<char>(byte));
                ++i;
            }
            else if ((byte & 0xE0) == 0xC0 && i + 1 < string.size())
            {
                char32_t c = ((byte & 0x1F) << 6) | (string.at(i + 1) & 0x3F);
                result.push_back(static_cast<char>(c));
                i += 2;
            }
            else
            {
                result.push_back('?');
                ++i;
            }
        }
        return result;
    }

    [[nodiscard]] inline constexpr const std::u8string convertUTF32ToUTF8(const std::u32string& string) noexcept
    {
        std::u8string result;
        for (const char32_t& c : string)
        {
            if (c <= 0x7F)
            {
                result.push_back(static_cast<char8_t>(c));
            }
            else if (c <= 0x7FF)
            {
                result.push_back(static_cast<char8_t>(0xC0 | ((c >> 6) & 0x1F)));
                result.push_back(static_cast<char8_t>(0x80 | (c & 0x3F)));
            }
            else if (c <= 0xFFFF)
            {
                result.push_back(static_cast<char8_t>(0xE0 | ((c >> 12) & 0x0F)));
                result.push_back(static_cast<char8_t>(0x80 | ((c >> 6) & 0x3F)));
                result.push_back(static_cast<char8_t>(0x80 | (c & 0x3F)));
            }
            else if (c <= 0x10FFFF)
            {
                result.push_back(static_cast<char8_t>(0xF0 | ((c >> 18) & 0x07)));
                result.push_back(static_cast<char8_t>(0x80 | ((c >> 12) & 0x3F)));
                result.push_back(static_cast<char8_t>(0x80 | ((c >> 6) & 0x3F)));
                result.push_back(static_cast<char8_t>(0x80 | (c & 0x3F)));
            }
            else
            {
                result.push_back(static_cast<char8_t>(0xEF));
                result.push_back(static_cast<char8_t>(0xBF));
                result.push_back(static_cast<char8_t>(0xBD));
            }
        }
        return result;
    }

    [[nodiscard]] inline constexpr const std::u32string convertUTF8ToUTF32(const std::u8string& string) noexcept
    {
        std::u32string result;
        std::size_t i = 0;
        const std::size_t n = string.size();
        while (i < n)
        {
            char32_t c = 0;
            std::uint8_t byte = static_cast<std::uint8_t>(string.at(i));
            if ((byte & 0x80) == 0x00)
            {
                c = byte;
                i += 1;
            }
            else if ((byte & 0xE0) == 0xC0 && i + 1 < n)
            {
                c = (byte & 0x1F) << 6;
                c |= (static_cast<std::uint8_t>(string.at(i + 1)) & 0x3F);
                i += 2;
            }
            else if ((byte & 0xF0) == 0xE0 && i + 2 < n)
            {
                c = (byte & 0x0F) << 12;
                c |= (static_cast<std::uint8_t>(string.at(i + 1)) & 0x3F) << 6;
                c |= (static_cast<std::uint8_t>(string.at(i + 2)) & 0x3F);
                i += 3;
            }
            else if ((byte & 0xF8) == 0xF0 && i + 3 < n)
            {
                c = (byte & 0x07) << 18;
                c |= (static_cast<std::uint8_t>(string.at(i + 1)) & 0x3F) << 12;
                c |= (static_cast<std::uint8_t>(string.at(i + 2)) & 0x3F) << 6;
                c |= (static_cast<std::uint8_t>(string.at(i + 3)) & 0x3F);
                i += 4;
            }
            else
            {
                c = 0xFFFD;
                i += 1;
            }
            result.push_back(c);
        }
        return result;
    }
}