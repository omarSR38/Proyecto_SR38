#include "DialogueBox.h"
#include <iostream>

#include "ResourceManager.h"
#include "Text/TextRenderer.h"

namespace {

    // Texto (píxeles lógicos)
    constexpr float CHAR_HEIGHT = 10.0f;   // alto de línea del texto
    constexpr float LINE_STEP = 12.0f;   // separación entre renglones
    constexpr int   MAX_LINES = 3;
    constexpr float PADDING_X = 8.0f;
    constexpr float PADDING_Y = 8.0f;

    // Parte el texto en renglones que quepan en maxWidth (respeta '\n').
    std::vector<std::string> wrapText(
        const TextRenderer& tr,
        const std::string& text,
        float maxWidth
    ) {
        std::vector<std::string> out;
        std::string line, word;

        auto flushWord = [&]() {
            if (word.empty()) return;
            std::string candidate = line.empty() ? word : line + " " + word;
            if (!line.empty() && tr.MeasureText(candidate, CHAR_HEIGHT, 0.0f) > maxWidth) {
                out.push_back(line);
                line = word;
            }
            else {
                line = candidate;
            }
            word.clear();
            };

        for (char c : text) {
            if (c == ' ') {
                flushWord();
            }
            else if (c == '\n') {
                flushWord();
                out.push_back(line);
                line.clear();
            }
            else {
                word += c;
            }
        }
        flushWord();
        if (!line.empty()) out.push_back(line);
        return out;
    }

} // namespace

///////////////////////////
////////CONSTRUCTORES//////

DialogueBox::DialogueBox() {
    currentIndex = 0;
    active = false;
}

////////////////////////
////////SET Y GET/////////

bool DialogueBox::isActive() const {
    return active;
}

const std::string& DialogueBox::getCurrentLine() const {

    static const std::string empty = "";

    if (!active || dialogueLines.empty()) {
        return empty;
    }

    return dialogueLines[currentIndex];
}

////////////////////////
////////METODOS/////////

void DialogueBox::open(const std::vector<std::string>& lines) {

    if (lines.empty()) return;

    dialogueLines = lines;

    currentIndex = 0;

    active = true;

    std::cout << "\n[DIALOGO]\n";
    std::cout << dialogueLines[currentIndex] << "\n";
}

void DialogueBox::advance() {

    if (!active) return;

    currentIndex++;

    if (currentIndex >= dialogueLines.size()) {
        close();
        return;
    }

    std::cout << "[DIALOGO]\n";
    std::cout << dialogueLines[currentIndex] << "\n";
}

void DialogueBox::close() {

    active = false;

    currentIndex = 0;

    dialogueLines.clear();

    std::cout << "[DIALOGO CERRADO]\n";
}

void DialogueBox::draw(const glm::mat4& projection, TextRenderer& text) const {

    if (!active) return;

    auto renderer = ResourceManager::GetRenderer("outline");
    auto spriteShader = ResourceManager::GetShader("sprite");

    if (!renderer) return;

    // Panel inferior
    glm::vec2 position(8.0f, 160.0f);
    glm::vec2 size(240.0f, 56.0f);

    // Fondo
    renderer->DrawRect(
        position,
        size,
        glm::vec4(0.025f, 0.035f, 0.09f, 1.0f),
        projection,
        true
    );

    // Contorno
    renderer->DrawRectOutline(
        position,
        size,
        glm::vec4(0.0f, 0.9f, 1.0f, 1.0f),
        projection
    );

    // Texto
    if (!spriteShader) return;

    const float maxWidth = size.x - 2.0f * PADDING_X;
    const auto lines = wrapText(text, getCurrentLine(), maxWidth);

    spriteShader->Use();
    spriteShader->PonMatriz4x4("projection", (float*)&projection[0][0]);

    for (int i = 0; i < static_cast<int>(lines.size()) && i < MAX_LINES; ++i) {
        text.DrawText(
            lines[i],
            glm::vec2(position.x + PADDING_X, position.y + PADDING_Y + i * LINE_STEP),
            CHAR_HEIGHT,
            0.0f,
            glm::vec3(1.0f)
        );
    }
}