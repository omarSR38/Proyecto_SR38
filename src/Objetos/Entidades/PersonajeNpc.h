// PersonajeNpc.h
#ifndef PERSONAJENPC_H
#define PERSONAJENPC_H
#include "Personaje.h"
#include <string>
#include <vector>
class PersonajeNpc : public Personaje {
public:
///////////////////////////
////////ATRIBUTOS/////////

///////////////////////////
////////CONSTRUCTORES//////
    PersonajeNpc(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);





///////////////////////////
/////SETTERS Y GETTERS/////
    void setDialogue(const std::vector<std::string>& lines);

    const std::vector<std::string>& getDialogue() const;
////////////////////////
////////METODOS/////////
    void update(float delta) override;

    void startDialogue();
    void nextDialogue();
    bool getIsTalking() const;
    const std::string& getCurrentDialogue() const;


private:

    ///////////////////////////
    //////ATRIBUTOS -///////
    std::vector<std::string> dialogueLines;
    size_t currentDialogueIndex = 0;
    bool isTalking = false;

};
#endif
