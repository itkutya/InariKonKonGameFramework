#include "InariKonKon/UI/Widgets/Text.hpp"

#include "InariKonKon/ECS/Components/Drawable.hpp"
#include "InariKonKon/UI/UIManager.hpp"

namespace ikk
{
    Text::Text(const Font& font, std::u32string_view text, Vec2f position, Vec2f scale, Degreef rotation, Color color) noexcept
        : UI(position, scale, rotation), m_text(text)
    {
        std::vector<UIVertex> vertexBuffer{};

        float x = 0.f;
        float y = 0.f;

        for (const char32_t& c : text)
        {
            //TODO:
            //Check if it exists if not idk empty box???
            const Font::Glyph& glyph = font.getAtlas().glyphs.at(c);

            float xpos = x + glyph.bearing.x();
            float ypos = y - glyph.bearing.y();

            auto w = glyph.size.x();
            auto h = glyph.size.y();

            // triangle 1
            vertexBuffer.push_back({
                .position = { xpos,     ypos + h },
                .color    = color,
                .texCoord = { glyph.textureRect.getLeft(),  glyph.textureRect.getBottom() }
            });

            vertexBuffer.push_back({
                .position = { xpos,     ypos },
                .color    = color,
                .texCoord = { glyph.textureRect.getLeft(),  glyph.textureRect.getTop() }
            });

            vertexBuffer.push_back({
                .position = { xpos + w, ypos },
                .color    = color,
                .texCoord = { glyph.textureRect.getRight(), glyph.textureRect.getTop() }
            });


            // triangle 2
            vertexBuffer.push_back({
                .position = { xpos,     ypos + h },
                .color    = color,
                .texCoord = { glyph.textureRect.getLeft(),  glyph.textureRect.getBottom() }
            });

            vertexBuffer.push_back({
                .position = { xpos + w, ypos },
                .color    = color,
                .texCoord = { glyph.textureRect.getRight(), glyph.textureRect.getTop() }
            });

            vertexBuffer.push_back({
                .position = { xpos + w, ypos + h },
                .color    = color,
                .texCoord = { glyph.textureRect.getRight(), glyph.textureRect.getBottom() }
            });

            x += glyph.advance.x();
        }

        std::vector<std::uint32_t> indexBuffer{};

        this->m_model = Model{vertexBuffer, indexBuffer};

        Drawable drawable
            {
                this->getModel(),
                UIManager::getInstance().getDefaultShaderProgram(),
                UIManager::getInstance().getDefaultUICamera(),
                &font.getAtlas().texture
            };

        this->addComponent(std::move(drawable));
    }
}