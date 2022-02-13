#pragma once
#include "functions.hpp"
#include "shaders.hpp"
#include <map>
#include <string>

// typedef class GameObject;
class Material {
private:
    Shader shader;
    std::map<std::string, int> intUniforms;
    std::map<std::string, float> floatUniforms;
    std::map<std::string, bool> boolUniforms;
    std::map<int, int> textures;
    friend class GameObject;

public:
    // Material(const Material &material);
    Material(const Shader &shader);
    Material(const Material &material);
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setTexture(std::string textureName, unsigned int textureUint, unsigned int textureID);
    void use();
};
