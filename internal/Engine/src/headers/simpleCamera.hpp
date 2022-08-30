#pragma once
#include "camera.hpp"

namespace Engine {
class SimpleCamera {
private:
    Camera mainCamera;

public:
    SimpleCamera(glm::vec3 startPos, glm::vec3 lookPos, Camera::Mode projectionMode);
    void update();
};
}