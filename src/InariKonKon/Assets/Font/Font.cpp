#include "InariKonKon/Assets/Font/Font.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "ft2build.h" // IWYU pragma: keep
#include FT_FREETYPE_H

#include "InariKonKon/Utility/Utility.hpp"

namespace ikk
{
    //TODO:
    //Async...
    Font::Font(const File& path, std::uint32_t fontSize) noexcept
        : m_fontSize(fontSize)
    {
        //TODO:
        /*
        struct FTLibrary { FT_Library lib; ~FTLibrary(){ FT_Done_FreeType(lib); } };
        struct FTFace { FT_Face face; ~FTFace(){ FT_Done_Face(face); } };
        */
        FT_Library library;
        if (FT_Init_FreeType(&library) != 0) return;

        FT_Face face;
        if (FT_New_Face(library, path.getPath().string().c_str(), 0, &face) != 0) { FT_Done_FreeType(library); return; }
        if (FT_Set_Pixel_Sizes(face, 0, fontSize) != 0) { FT_Done_Face(face); FT_Done_FreeType(library);return; }

        this->m_atlas.glyphs.reserve(face->num_glyphs);
        this->baseline = face->ascender * fontSize / (float)face->units_per_EM;

        static constexpr std::uint32_t maxTextureWidth = 1024;
        static constexpr std::uint32_t padding = 5u;
        static constexpr std::uint32_t bytesPerPixel = 1u;

        float penX = 0.0f;
        float penY = 0.0f;
        float maxRowWidth = 0.0f;
        float rowHeight = 0.0f;

        FT_UInt glyph_index;
        FT_ULong charcode = FT_Get_First_Char(face, &glyph_index);

        while (glyph_index != 0)
        {
            if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) == 0)
            {
                const FT_GlyphSlot& g = face->glyph;

                if (penX + g->bitmap.width > maxTextureWidth)
                {
                    maxRowWidth = std::max(maxRowWidth, penX - padding);
                    penX = 0.0f;
                    penY += (rowHeight + padding);
                    rowHeight = 0.0f;
                }

                Glyph glyph{};
                glyph.size    = { g->bitmap.width, g->bitmap.rows };
                glyph.bearing = { g->bitmap_left, g->bitmap_top };
                glyph.advance = { g->advance.x >> 6, g->advance.y >> 6 };

                glyph.textureRect.getLeft()   = penX;
                glyph.textureRect.getTop()    = penY;
                glyph.textureRect.getWidth()  = g->bitmap.width;
                glyph.textureRect.getHeight() = g->bitmap.rows;

                this->m_atlas.glyphs.emplace(static_cast<char32_t>(charcode), std::move(glyph));

                penX += g->bitmap.width + padding;
                rowHeight = std::max(rowHeight, F32(g->bitmap.rows));
            }
            charcode = FT_Get_Next_Char(face, charcode, &glyph_index);
        }

        this->m_atlas.width  = U32(std::max(maxRowWidth, penX));
        this->m_atlas.height = U32(penY + rowHeight);

        std::vector<std::byte> buffer = std::vector<std::byte>(this->m_atlas.width * this->m_atlas.height * bytesPerPixel, std::byte{0});
        for (auto& [key, glyph] : this->m_atlas.glyphs)
        {
            const FT_UInt index = FT_Get_Char_Index(face, key);
            if (FT_Load_Glyph(face, index, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL) != 0)
                continue;

            const FT_Bitmap& bitmap = face->glyph->bitmap;

            if (U32(glyph.textureRect.getLeft()) + bitmap.width > this->m_atlas.width ||
                U32(glyph.textureRect.getTop()) + bitmap.rows > this->m_atlas.height)
                return; //TODO:

            const std::byte* basePtr = reinterpret_cast<const std::byte*>(bitmap.buffer);
            if (bitmap.pitch < 0)
                basePtr += (bitmap.rows - 1) * std::size_t(-bitmap.pitch);

            for (std::size_t y = 0; y < bitmap.rows; ++y)
            {
                const std::size_t rowIndex = U32(glyph.textureRect.getTop()) + y;
                const std::size_t rowStart = rowIndex * this->m_atlas.width + U32(glyph.textureRect.getLeft());
                const std::byte* src = basePtr + std::ptrdiff_t(y) * std::abs(bitmap.pitch);

                std::memcpy(buffer.data() + rowStart, src, bitmap.width);
            }

            glyph.textureRect.getLeft()   /= F32(this->m_atlas.width);
            glyph.textureRect.getTop()    /= F32(this->m_atlas.height);
            glyph.textureRect.getWidth()  /= F32(this->m_atlas.width);
            glyph.textureRect.getHeight() /= F32(this->m_atlas.height);
        }

        this->m_atlas.texture.create(this->m_atlas.width, this->m_atlas.height, bytesPerPixel);
        this->m_atlas.texture.load(buffer);

        FT_Done_Face(face);
        FT_Done_FreeType(library);
    }

    const Font::Atlas& Font::getAtlas() const noexcept
    {
        return this->m_atlas;
    }
}