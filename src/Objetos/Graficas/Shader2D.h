#ifndef _SHADER_H_
#define _SHADER_H_

#include "OpenGLClass.h"
#include <string>
#include <fstream>
#include <iostream>

class Shader2D {
protected:
    //ATRIBUTOS A USAR:
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;
    unsigned int m_shaderProgram;
    ///////////////////

    //METODOS:
    bool CompileShader(unsigned int shader, const char* shaderSource, const char* shaderFilename);
    bool InitializeShader(const char* vsFilename, const char* fsFilename);
    void OutputShaderErrorMessage(unsigned int shaderId, const char* shaderFilename);
    void OutputLinkerErrorMessage(unsigned int programId);
    char* LoadShaderSourceFile(const char* filename);
    void ShutdownShader();
    //////////

    //SIN USAR (PARA REGISTRO):
    //OpenGLClass* OpenGL;          // Wrapper de OpenGL con funciones cargadas

public:
    //CONTRSTRUCTORES:
    Shader2D(OpenGLClass* OpenGL);
    Shader2D();
    virtual ~Shader2D();

    //SET Y GET:
    bool SetInt(const char* nombre, int valor);

    //METODOS:
    bool Initialize(const char* vsFilename, const char* fsFilename);
    void Shutdown();
    void Use();
    bool PonMatriz4x4(const char* nombre, const float* matriz);
    bool Pon1Entero(const char* nombre, unsigned int valor);
    bool PonVec3(const char* nombre, float* vector);
    bool PonVec4(const char* nombre, float* vector);
    virtual bool SetShaderParameters(float* param1, float* param2, float* param3);
    virtual void BindAttributeLocation();

};

#endif
