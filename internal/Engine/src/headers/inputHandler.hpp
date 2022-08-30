#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>

namespace Engine {
typedef class Engine Engine;
namespace InputHandler {

typedef struct mousePos {
    double x;
    double y;
} mousePos;

bool getKey(int key);
bool getKeyDown(int key);
bool getKeyUp(int key);
bool getKeyDown(std::string key);
bool getKey(std::string key);
bool getKeyUp(std::string key);
void bindKey(std::string keyName, int key);
const mousePos &getMousePosition();

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void init(Engine engine);
void update_keys();
void disableCursor(bool state);
void exit();

}; // namespace InputHandler
} // namespace Engine