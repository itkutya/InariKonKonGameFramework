#ifndef IKK_UPDATEABLE_HPP
#define IKK_UPDATEABLE_HPP

#include <functional>

namespace ikk
{
    class [[nodiscard]] Updateable final
    {
    public:
        [[nodiscard]] Updateable(std::function<void()> callback) noexcept;

        Updateable(const Updateable&) noexcept = default;
        Updateable(Updateable&&) noexcept = default;

        Updateable& operator=(const Updateable&) noexcept = default;
        Updateable& operator=(Updateable&&) noexcept = default;

        virtual ~Updateable() noexcept = default;

        void update() noexcept;
    private:
        std::function<void()> m_callback;
    };
}

#endif