#include "engine.hpp"
//#include "cameraNode.hpp"
#include "meshRenderer.hpp"
// #include "node.hpp"

namespace Engine {

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Engine *Engine::instance = NULL;

Engine::Engine(int width, int hight, const char *windowName) : input(*this) {
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

    // cout << glGetString(GL_VERSION) << endl;
}

void Engine::exit() {
    glfwSetWindowShouldClose(instance->window, true);
}

void Engine::update() {
    input.update_keys();
    for (auto node : nodes) {
        //(*it)->engineUpdate(*this);
    }
}

void Engine::addCameraCall(Node::Camera &camera) {
    cameraCalls.push_back(&camera);
}

void Engine::addDrawCall(Components::MeshRenderer &mesh) {
    drawcalls.push(&mesh);
}

void Engine::drawcall() {
    while (!drawcalls.empty()) {
        Components::MeshRenderer *renderer = drawcalls.top();
        for (auto camera : cameraCalls) {
            renderer->draw(*camera);
        }
        drawcalls.pop();
    }
    cameraCalls.clear();
}

void Engine::addNode(Node::Node *node) {
    nodes.push_back(node);
}

Engine::~Engine() {
    InputHandler::exit();
    glfwTerminate();
}

Engine &Engine::getEngine() {
    return (*instance);
}

GLFWwindow &Engine::getWindow() {
    return (*this->window);
}

} // namespace Engine
