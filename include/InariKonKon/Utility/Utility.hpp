#ifndef IKK_UTILITY_HPP
#define IKK_UTILITY_HPP

#include <concepts>
#include <cstdint>

#ifdef NDEBUG
    #define IKK_RELEASE
#else
    #define IKK_DEBUG
#endif

#define DEFINE_CAST_FUNC(NAME, TYPE)                                            \
template<class T> requires std::convertible_to<T, TYPE>                         \
inline constexpr TYPE NAME(T value) noexcept { return static_cast<TYPE>(value); }

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

constexpr const char8_t* TO_UTF8(const char* x) noexcept { return reinterpret_cast<const char8_t*>(x); }
constexpr const char* TO_ANSI(const char8_t* x) noexcept { return reinterpret_cast<const char*>(x); }

#endif