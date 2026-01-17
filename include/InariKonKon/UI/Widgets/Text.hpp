#pragma once

#include "InariKonKon/Assets/Font/Font.hpp"
#include "InariKonKon/UI/UI.hpp"

namespace ikk
{
    class [[nodiscard]] Text final : public UI
    {
    public:
        Text(const Font& font, std::u32string_view text, Vec2f position = {}, Vec2f scale = { 1.f, 1.f }, Degreef rotation = {}, Color color = Color::White) noexcept;

        Text(const Text&) noexcept = default;
        Text(Text&&) noexcept = default;

        Text& operator=(const Text&) noexcept = default;
        Text& operator=(Text&&) noexcept = default;

        ~Text() noexcept = default;
    private:
        std::u32string_view m_text;
    };
}