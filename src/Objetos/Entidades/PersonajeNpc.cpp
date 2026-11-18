// PersonajeNpc.cpp
#include "PersonajeNpc.h"

///////////////////////////
////////CONSTRUCTORES//////
PersonajeNpc::PersonajeNpc(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : Personaje(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection) {

}

////////////////////////
/////SETTERS Y GETTERS/////

void PersonajeNpc::setDialogue(
    const std::vector<std::string>& lines
) {
    dialogueLines = lines;

    // Reiniciar el estado de conversación
    currentDialogueIndex = 0;
    isTalking = false;
}

const std::vector<std::string>& PersonajeNpc::getDialogue() const {
    return dialogueLines;
}


////////////////////////
////////METODOS/////////
void PersonajeNpc::update(float delta) {
    // IA simple o comportamiento
    updateHitbox();
}




void PersonajeNpc::startDialogue() {

    if (dialogueLines.empty() || isTalking)
        return;

    currentDialogueIndex = 0;
    isTalking = true;
}


void PersonajeNpc::nextDialogue() {

    if (!isTalking)
        return;

    currentDialogueIndex++;

    if (currentDialogueIndex >= dialogueLines.size()) {
        isTalking = false;
        currentDialogueIndex = 0;
    }
}


bool PersonajeNpc::getIsTalking() const {
    return isTalking;
}


const std::string& PersonajeNpc::getCurrentDialogue() const {

    static const std::string emptyDialogue = "";

    if (!isTalking || dialogueLines.empty())
        return emptyDialogue;

    return dialogueLines[currentDialogueIndex];
}
