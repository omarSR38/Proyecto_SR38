#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Graficas/Texture2D.h"
#include "Graficas/Shader2D.h"
#include "Graficas/Renderer2D.h"
#include "CollRect.h"
//#include "Graficas/OpenGLClass.h"

class ResourceManager {
public:
    // Carga si no existe, devuelve shared_ptr
    static std::shared_ptr<Texture2D> LoadTexture(const std::string& key, const std::string& path, OpenGLClass* ogl, bool flipVertical = true);
    static std::shared_ptr<Texture2D> GetTexture(const std::string& key);

    static std::shared_ptr<Shader2D> LoadShader(const std::string& key, const std::string& vsPath, const std::string& fsPath, OpenGLClass* ogl);
    static std::shared_ptr<Shader2D> GetShader(const std::string& key);

    static std::shared_ptr<Renderer2D> GetOrCreateRenderer(const std::string& key, std::shared_ptr<Shader2D> shader);
    static std::shared_ptr<Renderer2D> GetRenderer(const std::string& key);



    // Libera todo (usar al cerrar)
    static void Clear();

private:
    static std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;
    static std::unordered_map<std::string, std::shared_ptr<Shader2D>> shaders;
    static std::unordered_map<std::string, std::shared_ptr<Renderer2D>> renderers;
};

#endif // RESOURCEMANAGER_H

