#pragma once

#include <unordered_map>

#include "InariKonKon/Assets/Texture/Texture.hpp"
#include "InariKonKon/Assets/File/File.hpp"
#include "InariKonKon/Math/Rect.hpp"
#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    class [[nodiscard]] Font final
    {
    public:
        struct [[nodiscard]] Glyph
        {
            Vec2u size{};
            Vec2i bearing{};
            Vec2I advance{};

            Rectf textureRect{};
        };

        struct [[nodiscard]] Atlas
        {
            std::uint32_t width = 0;
            std::uint32_t height = 0;

            std::unordered_map<char32_t, Glyph> glyphs{};
            Texture texture{};
        };

        [[nodiscard]] Font(const File& path, std::uint32_t fontSize) noexcept;

        Font(const Font&) noexcept = default;
        Font(Font&&) noexcept = default;

        Font& operator=(const Font&) noexcept = default;
        Font& operator=(Font&&) noexcept = default;

        ~Font() noexcept = default;

        const Atlas& getAtlas() const noexcept;

        float baseline = 0.f;
    private:
        std::uint32_t m_fontSize = 0;

        Atlas m_atlas{};
    };
}