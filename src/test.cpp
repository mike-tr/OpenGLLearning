//#include "camera.hpp"
// #include "cameraNode.hpp"
#include "engine.hpp"
// #include "etime.hpp"
// #include "gameObject.hpp"
// #include "math.h"
// #include "meshRenderer.hpp"
// #include "sceneNode.hpp"
// #include "shaders.hpp"
// #include "simpleCamera.hpp"
// #include "transformNode.hpp"

int testE() {
    std::cout << "creating scene!" << std::endl;
    // Engine::Node::Scene scene = Engine::Node::Scene();

    std::cout << "creating engine" << std::endl;
    Engine::Engine engine = Engine::Engine(800, 600, "test engine");

    std::cout << "done!" << std::endl;

    // GLFWwindow *window;

    // /* Initialize the library */
    // if (!glfwInit())
    //     return -1;

    // /* Create a windowed mode window and its OpenGL context */
    // window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    // if (!window) {
    //     glfwTerminate();
    //     return -1;
    // }

    // /* Make the window's context current */
    // glfwMakeContextCurrent(window);

    // GLenum err = glewInit();
    // if (err != GLEW_OK) {
    //     fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    // }

    // // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glfwTerminate();
    return 0;
}