#ifndef IKK_NON_MOVABLE_HPP
#define IKK_NON_MOVABLE_HPP

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

#endif