#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include "OpenGLClass.h"
#include "stb_image.h"
#include <iostream>

class Texture2D {
public:
///////////////////////////
////////ATRIBUTOS/////////

///////////////////////////
////////CONSTRUCTORES//////
    Texture2D(OpenGLClass* opengl);
    ~Texture2D();

///////////////////////////
/////SETTERS Y GETTERS/////
    int GetWidth() const;
    int GetHeight() const;

////////////////////////
////////METODOS/////////
    bool LoadFromFile(const std::string& filename, bool flipVertical = true);
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    void Release();

private:
///////////////////////////
////////ATRIBUTOS -///////
    unsigned int m_textureID;
    int m_width;
    int m_height;
    int m_channels;
};

#endif
