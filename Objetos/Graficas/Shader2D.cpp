#include "Shader2D.h"

Shader2D::Shader2D(OpenGLClass* OpenGL)
    : OpenGL(OpenGL), m_vertexShader(0), m_fragmentShader(0), m_shaderProgram(0) {}

Shader2D::~Shader2D() {
    Shutdown();
}

bool Shader2D::SetInt(const char* nombre, int valor) {
    int location = glGetUniformLocation(m_shaderProgram, nombre);
    if (location == -1) return false;
    glUniform1i(location, valor);
    return true;
}


bool Shader2D::Initialize(const char* vsFilename, const char* fsFilename) {
    return InitializeShader(vsFilename, fsFilename);
}

void Shader2D::Shutdown() {
    ShutdownShader();
}

void Shader2D::Use() {
    glUseProgram(m_shaderProgram);
}

bool Shader2D::InitializeShader(const char* vsFilename, const char* fsFilename) {
    const char* vertexSource = LoadShaderSourceFile(vsFilename);
    const char* fragmentSource = LoadShaderSourceFile(fsFilename);

    if (!vertexSource || !fragmentSource) return false;

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!CompileShader(m_vertexShader, vertexSource, vsFilename)) return false;
    if (!CompileShader(m_fragmentShader, fragmentSource, fsFilename)) return false;

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);

    BindAttributeLocation();  // Llamada virtual por si la clase hija define algo

    glLinkProgram(m_shaderProgram);

    GLint result;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        OutputLinkerErrorMessage(m_shaderProgram);
        return false;
    }

    delete[] vertexSource;
    delete[] fragmentSource;

    return true;
}

bool Shader2D::CompileShader(unsigned int shader, const char* shaderSource, const char* shaderFilename) {
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        OutputShaderErrorMessage(shader, shaderFilename);
        return false;
    }

    return true;
}

void Shader2D::ShutdownShader() {
    if (m_shaderProgram) {
        if (m_vertexShader) {
            glDetachShader(m_shaderProgram, m_vertexShader);
            glDeleteShader(m_vertexShader);
        }
        if (m_fragmentShader) {
            glDetachShader(m_shaderProgram, m_fragmentShader);
            glDeleteShader(m_fragmentShader);
        }

        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}

char* Shader2D::LoadShaderSourceFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return nullptr;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size + 1];
    if (!file.read(buffer, size)) {
        delete[] buffer;
        return nullptr;
    }

    buffer[size] = '\0'; // null terminator
    return buffer;
}

void Shader2D::OutputShaderErrorMessage(unsigned int shaderId, const char* shaderFilename) {
    GLint logSize = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

    char* log = new char[logSize];
    glGetShaderInfoLog(shaderId, logSize, nullptr, log);

    std::cerr << "Shader2D Compilation Error (" << shaderFilename << "):\n" << log << "\n";
    delete[] log;
}

void Shader2D::OutputLinkerErrorMessage(unsigned int programId) {
    GLint logSize = 0;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

    char* log = new char[logSize];
    glGetProgramInfoLog(programId, logSize, nullptr, log);

    std::cerr << "Shader2D Link Error:\n" << log << "\n";
    delete[] log;
}

bool Shader2D::PonMatriz4x4(const char* nombre, float* matriz) {
    GLint location = glGetUniformLocation(m_shaderProgram, nombre);
    if (location == -1) return false;
    glUniformMatrix4fv(location, 1, GL_FALSE, matriz);
    return true;
}

bool Shader2D::Pon1Entero(const char* nombre, unsigned int valor) {
    GLint location = glGetUniformLocation(m_shaderProgram, nombre);
    if (location == -1) return false;
    glUniform1i(location, valor);
    return true;
}

bool Shader2D::PonVec3(const char* nombre, float* vector) {
    GLint location = glGetUniformLocation(m_shaderProgram, nombre);
    if (location == -1) return false;
    glUniform3fv(location, 1, vector);
    return true;
}

bool Shader2D::PonVec4(const char* nombre, float* vector) {
    GLint location = glGetUniformLocation(m_shaderProgram, nombre);
    if (location == -1) return false;
    glUniform4fv(location, 1, vector);
    return true;
}

bool Shader2D::SetShaderParameters(float*, float*, float*) {
    // Clase base no implementa esto
    return true;
}

void Shader2D::BindAttributeLocation() {
    // Clase base no define nada, lo sobrescriben los hijos
    glBindAttribLocation(m_shaderProgram, 0, "aPos");
    glBindAttribLocation(m_shaderProgram, 1, "aTex");        // ¡coincide con tu VS!
}


 Shader2D::Shader2D() {

}