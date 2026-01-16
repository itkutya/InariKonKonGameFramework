#pragma once

namespace ikk
{
    class NonCopyable
    {
    public:
		constexpr NonCopyable() noexcept = default;

		constexpr NonCopyable(const NonCopyable&) noexcept = delete;
		constexpr NonCopyable(NonCopyable&&) noexcept = default;

		constexpr NonCopyable& operator=(const NonCopyable&) noexcept = delete;
		constexpr NonCopyable& operator=(NonCopyable&&) noexcept = default;

		virtual constexpr ~NonCopyable() noexcept = default;
    private:
    };
}