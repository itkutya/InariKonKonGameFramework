#include "InariKonKon/UI/Widgets/Text.hpp"

namespace ikk
{
    Model createModelFromText(const Font& font, std::u32string_view text, Color color) noexcept
    {
        std::vector<UIVertex> vertexBuffer{};
        vertexBuffer.reserve(text.size() * 4u);

        std::vector<std::uint32_t> indexBuffer{};
        indexBuffer.reserve(text.size() * 6u);

        float x = 0.f;
        for (const char32_t& c : text)
        {
            //TODO:
            //Report warning...
            if (font.getAtlas().glyphs.contains(c) == false)
                continue;

            const Font::Glyph& glyph = font.getAtlas().glyphs.at(c);

            const float w = glyph.size.x();
            const float h = glyph.size.y();

            const float xpos = x + glyph.bearing.x();
            const float ypos = font.baseline - glyph.bearing.y();

            const std::uint32_t startIndex = U32(vertexBuffer.size());

            vertexBuffer.emplace_back(UIVertex{
                .position = { xpos, ypos },
                .color    = color,
                .texCoord = { glyph.textureRect.getLeft(), glyph.textureRect.getTop() }
            });

            vertexBuffer.emplace_back(UIVertex{
                .position = { xpos, ypos + h },
                .color    = color,
                .texCoord = { glyph.textureRect.getLeft(), glyph.textureRect.getBottom() }
            });

            vertexBuffer.emplace_back(UIVertex{
                .position = { xpos + w, ypos },
                .color    = color,
                .texCoord = { glyph.textureRect.getRight(), glyph.textureRect.getTop() }
            });

            vertexBuffer.emplace_back(UIVertex{
                .position = { xpos + w, ypos + h },
                .color    = color,
                .texCoord = { glyph.textureRect.getRight(), glyph.textureRect.getBottom() }
            });

            indexBuffer.emplace_back(startIndex + 0);
            indexBuffer.emplace_back(startIndex + 1);
            indexBuffer.emplace_back(startIndex + 2);

            indexBuffer.emplace_back(startIndex + 2);
            indexBuffer.emplace_back(startIndex + 1);
            indexBuffer.emplace_back(startIndex + 3);

            x += glyph.advance.x();
        }

        return Model{ vertexBuffer, indexBuffer };
    }

    inline static constexpr std::string_view textVertexShader = R"(
        #version 460 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec4 color;
        layout(location = 2) in vec2 texCoord;

        out vec4 fragColor;
        out vec2 fragTexCoord;

        uniform mat3 model;

        layout (std140, binding = 0) uniform CameraMatrices
        {
            mat4 projection;
            mat4 view;
        };

        void main()
        {
            mat4 model3D = mat4(
                vec4(model[0][0], model[0][1], 0.0, 0.0),
                vec4(model[1][0], model[1][1], 0.0, 0.0),
                vec4(0.0        , 0.0        , 1.0, 0.0),
                vec4(model[2][0], model[2][1], 0.0, 1.0));
            gl_Position = projection * view * model3D * vec4(position, 1.0);

            fragColor = color;
            fragTexCoord = texCoord;
        })";

    inline static constexpr std::string_view textFragmentShader = R"(
        #version 460 core

        in vec4 fragColor;
        in vec2 fragTexCoord;

        out vec4 color;

        uniform sampler2D fontAtlas;

        void main()
        {
            color = vec4(fragColor.rgb, texture(fontAtlas, fragTexCoord).r);
        })";

    Text::Text(const Font& font, std::u32string_view text, Vec2f position, Vec2f scale, Degreef rotation, Color color) noexcept
        : Widget(
            { position, scale, rotation },
            createModelFromText(font, text, color),
            ShaderProgram{textVertexShader, textFragmentShader},
            &font.getAtlas().texture),
        m_text(text)
    {
    }
}