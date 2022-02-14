#include "etime.hpp"
#include "functions.hpp"

float ETime::lastFrame = 0.0f;
float ETime::deltaTime = 0.0f;

void ETime::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
