
#pragma once
#include "node.hpp"
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Engine {
class Engine {
private:
    static Engine *instance;
    GLFWwindow *window;

    std::list<Node *> nodes;

    /* data */
public:
    Engine(int width, int hight, char *windowName);
    ~Engine();
    static void exit();
    // Call each frame.
    void update();
    void addNode(Node *node);

    GLFWwindow &getWindow();

    static Engine &getEngine();
};
} // namespace Engine
