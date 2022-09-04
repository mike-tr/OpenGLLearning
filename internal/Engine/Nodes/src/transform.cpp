#include "Node/transform.hpp"

namespace Engine {
namespace Node {
Transform::Transform() {
    this->position = glm::vec3(0.0, 0.0, 0.0);
    this->rotationMatrix = glm::mat4(1.0f);
    this->scaleV = glm::vec3(1.0, 1.0, 1.0);
}

void Transform::localScale(glm::vec3 scale) {
    this->scaleV.x *= scale.x;
    this->scaleV.y *= scale.y;
    this->scaleV.z *= scale.z;
    this->recalculate();
}

glm::vec3 Transform::getPosition() {
    if (parent != nullptr)
        return this->parent->globalTransformMatrix * this->position;
    return this->position;
}

void Transform::setPosition(glm::vec3 pos) {
    this->position = pos;
}

void Transform::translate(glm::vec3 direction) {
    this->position = this->position + direction;
}

void Transform::localTranslate(glm::vec3 direction) {
    glm::vec4 t = glm::vec4(direction, 1.0f);
    this->position = this->position + glm::inverse(this->rotationMatrix) * t;
    this->recalculate();
}

void Transform::rotate(float degRadians, glm::vec3 axis) {
    this->rotationMatrix = glm::rotate(this->rotationMatrix, degRadians, axis);
    this->recalculate();
}

void Transform::recalculate() {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, this->position);
    trans = trans * this->rotationMatrix;
    trans = glm::scale(trans, this->scaleV);

    this->transformationMatrix = trans;
    if (this->parent != nullptr) {
        this->updateTransformMatrix(this->parent->getTransformMatrix());
    } else {
        this->updateTransformMatrix(glm::mat4(1.0f));
    }
}

void Transform::updateTransformMatrix(glm::mat4 const parentTransformMatrix) {
    this->globalTransformMatrix = parentTransformMatrix * this->transformationMatrix;
    for (auto node : nodes) {
        node->updateTransformMatrix(this->globalTransformMatrix);
    }
}

void Transform::lookAt(glm::vec3 target) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, this->position);

    this->rotationMatrix = glm::inverse(trans * glm::lookAt(this->position, target, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->transformationMatrix = this->rotationMatrix * glm::scale(trans, this->scaleV);
    if (this->parent != nullptr) {
        this->updateTransformMatrix(this->parent->getTransformMatrix());
    } else {
        this->updateTransformMatrix(glm::mat4(1.0f));
    }

    // this->rotationMatrix = glm::inverse(glm::lookAt(this->position, target, glm::vec3(0.0f, 1.0f, 0.0f)) * trans);
    // this->recalculate();
}

} // namespace Node
} // namespace Engine