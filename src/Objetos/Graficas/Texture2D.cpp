#include "Texture2D.h"

//CONTRSTRUCTORES:
Texture2D::Texture2D(OpenGLClass* opengl)
    :m_textureID(0), m_width(0), m_height(0), m_channels(0) {
}
Texture2D::~Texture2D() {
    Release();
}

//SET Y GET:
int Texture2D::GetWidth() const {
    return m_width;
}
int Texture2D::GetHeight() const {
    return m_height;
}

//METODOS:
bool Texture2D::LoadFromFile(const std::string& filename, bool flipVertical) {


    //stbi_set_flip_vertically_on_load(flipVertical);
    stbi_set_flip_vertically_on_load(false);

    unsigned char* data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);
    if (!data) {
        std::cerr << "Error al cargar la textura: " << filename << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    GLenum format = (m_channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
    return true;
}
void Texture2D::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture2D::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture2D::Release() {
    if (m_textureID) {
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;
    }
}

