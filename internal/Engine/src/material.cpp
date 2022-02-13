#include "material.hpp"

Material::Material(const Shader &shader) : shader(shader) {
}

Material::Material(const Material &material) : shader(material.shader) {
    // std::cout << "copy" << std::endl;
    this->boolUniforms.clear();
    this->floatUniforms.clear();
    this->intUniforms.clear();
    this->textures.clear();
    for (const auto &pair : material.boolUniforms) {
        boolUniforms[pair.first] = pair.second;
    }
    for (const auto &pair : material.intUniforms) {
        intUniforms[pair.first] = pair.second;
    }
    for (const auto &pair : material.floatUniforms) {
        floatUniforms[pair.first] = pair.second;
    }
    for (const auto &pair : material.textures) {
        textures[pair.first] = pair.second;
        // std::cout << pair.first << " ," << pair.second << std::endl;
    }
}

void Material::setBool(const std::string &name, bool value) {
    this->boolUniforms[name] = value;
}

void Material::setInt(const std::string &name, int value) {
    this->intUniforms[name] = value;
}

void Material::setFloat(const std::string &name, float value) {
    this->floatUniforms[name] = value;
}

void Material::setTexture(std::string textureName, unsigned int textureUint, unsigned int textureID) {
    this->setInt(textureName, textureUint);
    this->textures[textureUint] = textureID;
    // std::cout << textureName << " - "
    //           << "New val : " << textureID << " actuall new :" << this->textures.at(textureUint) << std::endl;
}

void Material::use() {
    shader.use();
    for (const auto &pair : boolUniforms) {
        shader.setBool(pair.first, pair.second);
    }
    for (const auto &pair : intUniforms) {
        shader.setInt(pair.first, pair.second);
    }
    for (const auto &pair : floatUniforms) {
        shader.setFloat(pair.first, pair.second);
    }
    for (const auto &pair : textures) {
        glActiveTexture(GL_TEXTURE0 + pair.first);
        glBindTexture(GL_TEXTURE_2D, pair.second);
        // std::cout << pair.first << " ," << pair.second << std::endl;
    }
}