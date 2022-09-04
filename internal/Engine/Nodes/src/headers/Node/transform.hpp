#pragma once
#include "functions.hpp"
#include "node.hpp"

namespace Engine {
namespace Node {
class Transform : public Node {
private:
    glm::mat4 rotationMatrix;
    glm::vec3 scaleV;
    glm::mat4 transformationMatrix;
    glm::vec3 position;

protected:
    void updateTransformMatrix(glm::mat4 const parentTransformMatrix) override;

public:
    Transform();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);
    void translate(glm::vec3 direction);
    void localTranslate(glm::vec3 direction);
    void localScale(glm::vec3 scale);
    void rotate(float degRadians, glm::vec3 axis);
    void recalculate();
    void applyTransformation(unsigned int transformLoc);
};
} // namespace Node
} // namespace Engine