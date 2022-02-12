#pragma once
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec);
std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);
glm::vec3 operator+(const glm::vec3 &base, const glm::vec4 &other);
glm::vec3 operator-(const glm::vec3 &base, const glm::vec4 &other);