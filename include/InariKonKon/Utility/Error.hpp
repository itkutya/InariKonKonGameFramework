#pragma once

#include <string_view>

namespace ikk
{
    class [[nodiscard]] Error
    {
    public:
        [[nodiscard]] explicit constexpr Error(std::string_view description) noexcept;

        constexpr Error(const Error&) noexcept = default;
        constexpr Error(Error&&) noexcept = default;

        constexpr Error& operator=(const Error&) noexcept = default;
        constexpr Error& operator=(Error&&) noexcept = default;

        [[nodiscard]] constexpr const std::string_view& what() const noexcept;
    private:
        std::string_view m_description;
    };

    constexpr Error::Error(std::string_view description) noexcept
        : m_description(description)
    {
    }

    constexpr const std::string_view& Error::what() const noexcept
    {
        return this->m_description;
    }
}