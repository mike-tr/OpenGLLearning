#include "inputHandler.hpp"
#include "engine.hpp"
#include <queue>

namespace Engine {
std::map<int, int> keyStates;
std::map<std::string, int> keyMaps;
std::queue<int> keyPending;

Engine *engine = NULL;

InputHandler::mousePos pos;

#define KEY_DOWN 1
#define KEY_PRESSED 2
#define KEY_UP 3
#define KEY_RELEASED 0

void InputHandler::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (action) {
    case GLFW_PRESS:
        keyStates[key] = KEY_DOWN;
        keyPending.push(key);
        break;
    case GLFW_RELEASE:
        keyStates[key] = KEY_UP;
        keyPending.push(key);
        break;
    default:
        break;
    }
    keyStates[key] = action + 1;
}

void InputHandler::update_keys() {
    while (!keyPending.empty()) {
        int next = keyPending.front();
        keyPending.pop();

        if (keyStates[next] == KEY_DOWN) {
            keyStates[next] = KEY_PRESSED;
        } else if (keyStates[next] == KEY_UP) {
            keyStates[next] = KEY_RELEASED;
        }
    }
}

void init(Engine *global_engine) {
    keyStates.clear();
    keyMaps.clear();
    std::queue<int> empty;
    std::swap(keyPending, empty);
    engine = global_engine;
}

bool InputHandler::getKey(int key) {
    return keyStates[key];
}

bool InputHandler::getKeyDown(int key) {
    return keyStates[key] == GLFW_PRESS + 1;
}

bool InputHandler::getKeyUp(int key) {
    return keyStates[key] == GLFW_RELEASE + 1;
}

bool InputHandler::getKeyDown(std::string key) {
    return getKeyDown(keyMaps[key]);
}

bool InputHandler::getKey(std::string key) {
    return getKey(keyMaps[key]);
}

bool InputHandler::getKeyUp(std::string key) {
    return getKeyUp(keyMaps[key]);
}

void InputHandler::bindKey(std::string keyName, int key) {
    keyMaps[keyName] = key;
}

void InputHandler::disableCursor(bool state) {
    glfwSetInputMode(&engine->getWindow(), GLFW_CURSOR, state ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    pos.x = xpos;
    pos.y = ypos;
}

const InputHandler::mousePos &InputHandler::getMousePosition() {
    return pos;
}

} // namespace Engine