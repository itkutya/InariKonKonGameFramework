#include "InariKonKon/Assets/Font/Font.hpp"

#include <algorithm>

#include "ft2build.h" // IWYU pragma: keep
#include FT_FREETYPE_H

#include "InariKonKon/Utility/Utility.hpp"

#include "InariKonKon/Core/ExternalLibraries/OpenGL.hpp" // IWYU pragma: keep

namespace ikk
{
    Font::Font(const File& path, std::uint32_t fontSize) noexcept
        : m_fontSize(fontSize)
    {
        FT_Library library;
        if (FT_Init_FreeType(&library)) return;

        FT_Face face;
        if (FT_New_Face(library, path.getPath().string().c_str(), 0, &face)) { FT_Done_FreeType(library); return; }
        if (FT_Set_Pixel_Sizes(face, 0, fontSize)) { FT_Done_Face(face); FT_Done_FreeType(library);return; }

        this->m_atlas.glyphs.reserve(face->num_glyphs);

        static constexpr std::uint32_t maxTextureWidth = 1024;
        static constexpr std::uint32_t bytesPerPixel = 1u;
        static constexpr std::uint32_t padding = 5u;

        float penX = 0.0f;
        float penY = 0.0f;
        float maxRowWidth = 0.0f;
        float rowHeight = 0.0f;

        FT_UInt glyph_index;
        FT_ULong charcode = FT_Get_First_Char(face, &glyph_index);

        while (glyph_index != 0)
        {
            if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT | FT_LOAD_TARGET_NORMAL) == 0)
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

        this->m_atlas.texture.create(this->m_atlas.width, this->m_atlas.height, bytesPerPixel);
        std::vector<std::byte>& buffer = this->m_atlas.texture.getBuffer();

        for (auto& [key, glyph] : this->m_atlas.glyphs)
        {
            const FT_UInt index = FT_Get_Char_Index(face, key);
            if (FT_Load_Glyph(face, index, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL) != 0)
                continue;

            const FT_Bitmap& bitmap = face->glyph->bitmap;
            for (std::uint32_t y = 0; y < bitmap.rows; ++y)
            {
                const std::uint32_t dstY = U32(glyph.textureRect.getTop()) + y;
                const std::uint32_t rowStart = (dstY * this->m_atlas.width + U32(glyph.textureRect.getLeft())) * bytesPerPixel;

                for (std::uint32_t x = 0; x < bitmap.width; ++x)
                    buffer[rowStart + x] = std::byte{ bitmap.buffer[y * bitmap.pitch + x] };
            }

            glyph.textureRect.getLeft()   /= F32(this->m_atlas.width);
            glyph.textureRect.getTop()    /= F32(this->m_atlas.height);
            glyph.textureRect.getWidth()  /= F32(this->m_atlas.width);
            glyph.textureRect.getHeight() /= F32(this->m_atlas.height);
        }

        /*
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        static GLuint tex = 0;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_R8,
            m_atlas.width,
            m_atlas.height,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            buffer.data()
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        */

        FT_Done_Face(face);
        FT_Done_FreeType(library);
    }
}