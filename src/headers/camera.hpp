#pragma once
#include "functions.hpp"

class Camera {
private:
    glm::mat4 rotationMatrix;
    glm::vec3 scaleV;
    glm::mat4 transformationMatrix;
    glm::vec3 position;

public:
    static Camera mainCamera;
    Camera(glm::vec3 startPos);
    void rotate(float degree, glm::vec3 axis);
    void scale(glm::vec3 scale);
    void apply(unsigned int shader);
    void recalculate();
    void localTranslate(glm::vec3 translate);
    void globalTranslate(glm::vec3 translate);
    glm::vec3 getPos();
};
