#include "functions.hpp"

class GameObject {
private:
public:
    unsigned int object;
    GameObject(unsigned int model);
    void render();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);
    void localTranslate(glm::vec3 direction);
    void localScale(glm::vec3 scale);
    void rotate(float degRadians, glm::vec3 axis);
};