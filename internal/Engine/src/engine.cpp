#include "engine.hpp"
#include "inputHandler.hpp"

namespace Engine {

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Engine *Engine::instance = NULL;

Engine::Engine(int width, int hight, char *windowName) {
    if (instance != NULL) {
        std::cerr << "Can have only 1 instance of engine running!" << std::endl;
    }
    instance = this;

    this->window = glfwCreateWindow(width, hight, windowName, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, InputHandler::key_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glfwSetCursorPosCallback(window, mouse_callback);

    // cout << glGetString(GL_VERSION) << endl;
}

void Engine::exit() {
    glfwSetWindowShouldClose(instance->window, true);
}

void Engine::update() {

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        (*it)->engineUpdate();
    }
}

void Engine::addNode(Node *node) {
    nodes.push_back(node);
}

Engine::~Engine() {
}

Engine &Engine::getEngine() {
    return (*instance);
}

GLFWwindow &Engine::getWindow() {
    return (*this->window);
}

} // namespace Engine
