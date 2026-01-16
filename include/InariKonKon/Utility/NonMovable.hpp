#pragma once

namespace ikk
{
    class NonMovable
    {
    public:
		constexpr NonMovable() noexcept = default;

		constexpr NonMovable(const NonMovable&) noexcept = default;
		constexpr NonMovable(NonMovable&&) noexcept = delete;

		constexpr NonMovable& operator=(const NonMovable&) noexcept = default;
		constexpr NonMovable& operator=(NonMovable&&) noexcept = delete;

		virtual constexpr ~NonMovable() noexcept = default;
    private:
    };
}