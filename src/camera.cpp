#include "camera.hpp"

Camera Camera::mainCamera = Camera(glm::vec3(0.0, 0.0, 0.0));

Camera::Camera(glm::vec3 startPos) {
    this->position = startPos;
    this->rotationMatrix = glm::mat4(1.0f);
    this->scaleV = glm::vec3(1.0, 1.0, 1.0);
    this->recalculate();
}

void Camera::rotate(float radians, glm::vec3 axis) {
    this->rotationMatrix = glm::rotate(this->rotationMatrix, radians, axis);
    this->recalculate();
}

void Camera::scale(glm::vec3 scale) {
    this->scaleV.x *= scale.x;
    this->scaleV.y *= scale.y;
    this->scaleV.z *= scale.z;
    this->recalculate();
}

void Camera::apply(unsigned int shader) {
    unsigned int transformLoc = glGetUniformLocation(shader, "camera");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(this->transformationMatrix));
}

void Camera::recalculate() {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = trans * this->rotationMatrix;
    trans = glm::translate(trans, -this->position);
    trans = glm::scale(trans, this->scaleV);

    this->transformationMatrix = trans;
}

void Camera::localTranslate(glm::vec3 translate) {
    glm::vec4 t = glm::vec4(translate, 1.0f);
    this->position = this->position + glm::inverse(this->rotationMatrix) * t;
    this->recalculate();
}

void Camera::globalTranslate(glm::vec3 translate) {
    this->position += translate;
    this->recalculate();
}

glm::vec3 Camera::getPos() {
    return this->position;
}
