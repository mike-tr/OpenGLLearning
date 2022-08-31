
#pragma once
#include "componenets.fwd.hpp"

#include "inputHandler.hpp"
#include "node.hpp"
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <list>
#include <stack>

// typedef class InputHandler;

namespace Engine {
class Engine {
private:
    friend class InputHandler;
    static Engine *instance;
    InputHandler input;
    GLFWwindow *window;

    std::list<Node::Node *> nodes;
    std::stack<Components::Mesh *> drawcalls;
    // std::stack<Cam>

    void addDrawCall(Components::Mesh &mesh);
    void drawcall();
    /* data */
public:
    Engine(int width, int hight, char *windowName);
    ~Engine();
    static void exit();
    // Call each frame.
    void update();
    void addNode(Node::Node *node);

    GLFWwindow &getWindow();

    static Engine &getEngine();
};
} // namespace Engine