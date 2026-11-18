
#include "TextRenderer.h"
#include <algorithm>
#include <cmath>

TextRenderer::TextRenderer(
    std::shared_ptr<Renderer2D> renderer_,
    std::shared_ptr<Texture2D> fontTexture_
)
    : renderer(renderer_),
    fontTexture(fontTexture_)
{
}

void TextRenderer::SetGlyph(
    unsigned char character,
    int x,
    int y,
    int width,
    int height,
    float advance
) {
    // Glifo sin región (p. ej. el espacio): solo avanza, no se dibuja.
    if (width <= 0 || height <= 0) {
        Glyph blank;
        blank.advance = advance;
        glyphs[character] = blank;
        return;
    }

    if (!fontTexture)
        return;

    // Comprobar que el glifo esté dentro del atlas.
    if (x < 0 || y < 0 ||
        x + width > fontTexture->GetWidth() ||
        y + height > fontTexture->GetHeight()) {
        return;
    }

    Glyph glyph;

    glyph.x = x;
    glyph.y = y;
    glyph.width = width;
    glyph.height = height;
    glyph.advance = advance;

    glyphs[character] = glyph;
    lineHeight = (std::max)(lineHeight, height);
}

void TextRenderer::ClearGlyphs() {
    glyphs.clear();
    lineHeight = 0;
}

void TextRenderer::DrawText(
    const std::string& text,
    const glm::vec2& position,
    float characterHeight,
    float spacing,
    const glm::vec3& color
) {
    if (!renderer || !fontTexture || lineHeight <= 0) return;

    const float texW = static_cast<float>(fontTexture->GetWidth());
    const float texH = static_cast<float>(fontTexture->GetHeight());
    const float scale = characterHeight / static_cast<float>(lineHeight);

    float cursorX = position.x;
    float cursorY = position.y;

    for (unsigned char c : text) {

        if (c == '\n') {
            cursorX = position.x;
            cursorY += characterHeight;
            continue;
        }

        auto it = glyphs.find(c);
        if (it == glyphs.end()) {
            it = glyphs.find('?');          // carácter desconocido
            if (it == glyphs.end()) continue;
        }
        const Glyph& g = it->second;

        // Dibujar solo si tiene región (el espacio no tiene).
        if (g.width > 0 && g.height > 0) {
            renderer->DrawSpriteRegion(
                fontTexture.get(),
                // Redondeo para que los píxeles de la fuente no "tiemblen".
                glm::vec2(std::round(cursorX), std::round(cursorY)),
                glm::vec2(g.width * scale, g.height * scale),
                0.0f,
                glm::vec2(g.x / texW, g.y / texH),
                glm::vec2(g.width / texW, g.height / texH),
                color
            );
        }

        const float adv = (g.advance > 0.0f) ? g.advance : static_cast<float>(g.width);
        cursorX += adv * scale + spacing;
    }
}



float TextRenderer::MeasureText(
    const std::string& text,
    float characterHeight,
    float spacing
) const {
    if (lineHeight <= 0) return 0.0f;

    const float scale = characterHeight / static_cast<float>(lineHeight);
    float best = 0.0f, cur = 0.0f;

    for (unsigned char c : text) {
        if (c == '\n') { best = (std::max)(best, cur); cur = 0.0f; continue; }

        auto it = glyphs.find(c);
        if (it == glyphs.end()) it = glyphs.find('?');
        if (it == glyphs.end()) continue;

        const Glyph& g = it->second;
        const float adv = (g.advance > 0.0f) ? g.advance : static_cast<float>(g.width);
        cur += adv * scale + spacing;
    }
    return (std::max)(best, cur);
}