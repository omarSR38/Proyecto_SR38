
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <string>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "../Graficas/Renderer2D.h"
#include "../Graficas/Texture2D.h"

class TextRenderer {
public:

    struct Glyph {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        // Avance horizontal en píxeles del atlas.
        // Si es 0, se utiliza el ancho del glifo.
        float advance = 0.0f;
    };

    TextRenderer(
        std::shared_ptr<Renderer2D> renderer,
        std::shared_ptr<Texture2D> fontTexture
    );

    // Registra un carácter y su región dentro del atlas.
    void SetGlyph(
        unsigned char character,
        int x,
        int y,
        int width,
        int height,
        float advance = 0.0f
    );

    // Elimina todos los caracteres registrados.
    void ClearGlyphs();

    // Dibuja una cadena utilizando una altura uniforme.
    void DrawText(
        const std::string& text,
        const glm::vec2& position,
        float characterHeight,
        float spacing,
        const glm::vec3& color
    );

    // Ancho en píxeles lógicos de la línea más ancha (útil para centrar o ajustar).
    float MeasureText(
        const std::string& text,
        float characterHeight,
        float spacing
    ) const;

private:

    std::shared_ptr<Renderer2D> renderer;
    std::shared_ptr<Texture2D> fontTexture;

    std::unordered_map<unsigned char, Glyph> glyphs;

    // Alto máximo de los glifos registrados (define la escala).
    int lineHeight = 0;

};

#endif
