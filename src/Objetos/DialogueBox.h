#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <string>
#include <vector>
#include <cstddef>
#include <glm/glm.hpp>

class TextRenderer;

class DialogueBox {
public:

    ///////////////////////////
    ////////ATRIBUTOS/////////

    ///////////////////////////
    //////CONSTRUCTORES//////

    DialogueBox();

    ///////////////////////////
    /////SETTERS Y GETTERS/////

    bool isActive() const;
    const std::string& getCurrentLine() const;

    ////////////////////////
    ////////METODOS/////////

    void open(const std::vector<std::string>& lines);
    void advance();
    void close();

    void draw(const glm::mat4& projection, TextRenderer& text) const;

private:

    ///////////////////////////
    //////ATRIBUTOS -///////

    std::vector<std::string> dialogueLines;

    size_t currentIndex = 0;

    bool active = false;

};

#endif