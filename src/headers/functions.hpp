#pragma once
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// class Engine {
// public:
//     Engine(int width, int height);
// };

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
unsigned int load_shaders();
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int create_texture(const char *imagePath);
