#ifndef _SHADER_H_
#define _SHADER_H_

#include "OpenGLClass.h"
#include <string>
#include <fstream>
#include <iostream>

class Shader2D {
protected:
    OpenGLClass* OpenGL;          // OpenGL wrapper con punteros a funciones
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;
    unsigned int m_shaderProgram;

    bool CompileShader(unsigned int shader, const char* shaderSource, const char* shaderFilename);
    bool InitializeShader(const char* vsFilename, const char* fsFilename);

    void OutputShaderErrorMessage(unsigned int shaderId, const char* shaderFilename);
    void OutputLinkerErrorMessage(unsigned int programId);
    char* LoadShaderSourceFile(const char* filename);
    void ShutdownShader();

public:
    Shader2D(OpenGLClass* OpenGL);
    Shader2D();
    virtual ~Shader2D();

    bool Initialize(const char* vsFilename, const char* fsFilename);
    void Shutdown();
    void Use();

    bool PonMatriz4x4(const char* nombre, float* matriz);
    bool Pon1Entero(const char* nombre, unsigned int valor);
    bool PonVec3(const char* nombre, float* vector);
    bool PonVec4(const char* nombre, float* vector);

    // Métodos virtuales
    virtual bool SetShaderParameters(float* param1, float* param2, float* param3);
    virtual void BindAttributeLocation();

    bool SetInt(const char* nombre, int valor);
};

#endif
