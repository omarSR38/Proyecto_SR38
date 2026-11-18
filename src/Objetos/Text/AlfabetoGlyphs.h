// Generado a partir de alfabeto_transparente.png (1000 x 1150 px).
// Todos los glifos comparten la misma banda vertical (y = celda + 27, alto = 85),
// por lo que la línea base queda alineada sin cálculos extra.
// Cada "píxel" de la fuente mide ~8.57 px en el atlas (5x7 px para mayúsculas).
#pragma once
#include "TextRenderer.h"

inline void RegisterAlfabetoGlyphs(TextRenderer& t) {
    constexpr int   BAND_H = 85;   // alto común de todos los glifos en el atlas
    constexpr float GAP = 9.0f; // separación entre caracteres (~1 píxel de fuente)
    auto g = [&](char c, int x, int y, int w) {
        t.SetGlyph(static_cast<unsigned char>(c), x, y, w, BAND_H, w + GAP);
        };

    t.ClearGlyphs();
    // Espacio: no dibuja nada, solo avanza (~4 píxeles de fuente).
    t.SetGlyph(' ', 0, 0, 0, 0, 34.0f);

    // Mayúsculas A-I
    g('A', 34, 27, 43);
    g('B', 144, 27, 43);
    g('C', 254, 27, 43);
    g('D', 364, 27, 43);
    g('E', 474, 27, 43);
    g('F', 584, 27, 42);
    g('G', 694, 27, 43);
    g('H', 804, 27, 43);
    g('I', 914, 27, 43);

    // Mayúsculas J-R
    g('J', 34, 147, 43);
    g('K', 144, 147, 43);
    g('L', 254, 147, 43);
    g('M', 364, 147, 43);
    g('N', 474, 147, 43);
    g('O', 584, 147, 42);
    g('P', 694, 147, 43);
    g('Q', 800, 147, 51);
    g('R', 914, 147, 43);

    // Mayúsculas S-Z
    g('S', 34, 267, 43);
    g('T', 144, 267, 42);
    g('U', 254, 267, 43);
    g('V', 364, 267, 43);
    g('W', 474, 267, 43);
    g('X', 584, 267, 43);
    g('Y', 694, 267, 43);
    g('Z', 804, 267, 43);

    // Minúsculas a-i
    g('a', 34, 411, 43);
    g('b', 148, 411, 34);
    g('c', 258, 411, 34);
    g('d', 368, 411, 34);
    g('e', 474, 411, 43);
    g('f', 588, 411, 34);
    g('g', 698, 411, 34);
    g('h', 808, 411, 34);
    g('i', 922, 411, 26);

    // Minúsculas j-r
    g('j', 38, 531, 34);
    g('k', 148, 531, 34);
    g('l', 271, 531, 9);
    g('m', 364, 531, 43);
    g('n', 478, 531, 34);
    g('o', 584, 531, 42);
    g('p', 698, 531, 34);
    g('q', 808, 531, 34);
    g('r', 918, 531, 34);

    // Minúsculas s-z
    g('s', 38, 651, 34);
    g('t', 148, 651, 34);
    g('u', 258, 651, 34);
    g('v', 364, 651, 42);
    g('w', 474, 651, 43);
    g('x', 584, 651, 43);
    g('y', 698, 651, 34);
    g('z', 804, 651, 43);

    // Dígitos 0-8
    g('0', 34, 795, 43);
    g('1', 152, 795, 26);
    g('2', 254, 795, 43);
    g('3', 364, 795, 43);
    g('4', 474, 795, 43);
    g('5', 588, 795, 34);
    g('6', 694, 795, 43);
    g('7', 804, 795, 42);
    g('8', 914, 795, 43);

    // 9 y signos . , ; : $ # ' !
    g('9', 34, 915, 43);
    g('.', 161, 915, 9);
    g(',', 267, 915, 17);
    g(';', 377, 915, 17);
    g(':', 491, 915, 9);
    g('$', 584, 915, 43);
    g('#', 694, 915, 43);
    g('\'', 821, 915, 9);
    g('!', 931, 915, 9);

    // Signos " / ? % & ( ) @
    g('"', 42, 1035, 26);
    g('/', 148, 1035, 34);
    g('?', 254, 1035, 43);
    g('%', 351, 1035, 68);
    g('&', 470, 1035, 51);
    g('(', 597, 1035, 17);
    g(')', 707, 1035, 17);
    g('@', 795, 1035, 60);
}