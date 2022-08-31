
#pragma once
#include "componenets.fwd.hpp"
#include "inputHandler.hpp"
#include "nodes.fwd.hpp"

#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stack>
#include <vector>

// typedef class InputHandler;

namespace Engine {
class Engine {
private:
    friend class InputHandler;
    friend class Components::MeshRenderer;
    friend class Node::Camera;
    static Engine *instance;
    InputHandler input;
    GLFWwindow *window;

    std::vector<Node::Node *> nodes;
    std::stack<Components::MeshRenderer *> drawcalls;
    std::vector<Node::Camera *> cameraCalls;
    //  std::stack<Cam>

    void addDrawCall(Components::MeshRenderer &mesh);
    void addCameraCall(Node::Camera &camera);
    void drawcall();
    /* data */
public:
    Engine(int width, int hight, const char *windowName);
    ~Engine();
    static void exit();
    // Call each frame.
    void update();
    void addNode(Node::Node *node);

    GLFWwindow &getWindow();

    static Engine &getEngine();
};
} // namespace Engine