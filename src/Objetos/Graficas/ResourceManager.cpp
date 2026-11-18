#include "ResourceManager.h"
#include <iostream>

// definición de maps estáticos
std::unordered_map<std::string, std::shared_ptr<Texture2D>> ResourceManager::textures;
std::unordered_map<std::string, std::shared_ptr<Shader2D>> ResourceManager::shaders;
std::unordered_map<std::string, std::shared_ptr<Renderer2D>> ResourceManager::renderers;

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& key, const std::string& path, OpenGLClass* ogl, bool flipVertical) {
    auto it = textures.find(key);
    if (it != textures.end()) return it->second;

    auto tex = std::make_shared<Texture2D>(ogl);
    if (!tex->LoadFromFile(path, flipVertical)) {
        std::cerr << "ResourceManager::LoadTexture - fallo al cargar: " << path << "\n";
        return nullptr;
    }
    textures[key] = tex;
    return tex;
}

std::shared_ptr<Texture2D> ResourceManager::GetTexture(const std::string& key) {
    auto it = textures.find(key);
    return (it != textures.end()) ? it->second : nullptr;
}

std::shared_ptr<Shader2D> ResourceManager::LoadShader(const std::string& key, const std::string& vsPath, const std::string& fsPath, OpenGLClass* ogl) {
    auto it = shaders.find(key);
    if (it != shaders.end()) return it->second;

    auto sh = std::make_shared<Shader2D>(ogl);
    if (!sh->Initialize(vsPath.c_str(), fsPath.c_str())) {
        std::cerr << "ResourceManager::LoadShader - fallo al compilar shader: " << vsPath << " / " << fsPath << "\n";
        return nullptr;
    }
    shaders[key] = sh;
    return sh;
}

std::shared_ptr<Shader2D> ResourceManager::GetShader(const std::string& key) {
    auto it = shaders.find(key);
    return (it != shaders.end()) ? it->second : nullptr;
}

std::shared_ptr<Renderer2D> ResourceManager::GetOrCreateRenderer(const std::string& key, std::shared_ptr<Shader2D> shader) {
    auto it = renderers.find(key);
    if (it != renderers.end()) return it->second;

    if (!shader) return nullptr;
    auto rend = std::make_shared<Renderer2D>(shader); // constructor actual toma Shader2D&
    // Si cambiamos Renderer2D para aceptar shared_ptr<Shader2D>, ajusta aquí
    renderers[key] = rend;
    return rend;
}

std::shared_ptr<Renderer2D> ResourceManager::GetRenderer(const std::string& key) {
    auto it = renderers.find(key);
    return (it != renderers.end()) ? it->second : nullptr;
}

void ResourceManager::Clear() {
    // liberar en orden: renderers -> textures -> shaders
    renderers.clear();
    textures.clear();
    // llamamos a shutdown de shaders si es necesario
    for (auto& p : shaders) {
        if (p.second) p.second->Shutdown();
    }
    shaders.clear();
}
