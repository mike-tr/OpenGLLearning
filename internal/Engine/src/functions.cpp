#define STB_IMAGE_IMPLEMENTATION
#include "camera.hpp"

using namespace std;

#define ENDING 4

bool wireframe = false;

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

glm::vec3 operator+(const glm::vec3 &base, const glm::vec4 &other) {
    glm::vec3 n = base;
    glm::vec4 no = other / other.w;
    n.x += no.x;
    n.y += no.y;
    n.z += no.z;
    return n;
}

glm::vec3 operator-(const glm::vec3 &base, const glm::vec4 &other) {
    glm::vec3 n = base;
    glm::vec4 no = other / other.w;
    n.x -= no.x;
    n.y -= no.y;
    n.z -= no.z;
    return n;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        wireframe = !wireframe;
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    } else if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        Camera::mainCamera.localTranslate(glm::vec3(0.0, 1.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(0.0, 1.0, 0.0) * 0.01f;
        // cout << Camera::mainCamera.position.x << ", " << Camera::mainCamera.position.y << ", "
        //      << Camera::mainCamera.position.z << endl;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        Camera::mainCamera.localTranslate(glm::vec3(0.0, -1.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(0.0, -1.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        Camera::mainCamera.localTranslate(glm::vec3(1.0, 0.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(1.0, 0.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        Camera::mainCamera.localTranslate(glm::vec3(-1.0, 0.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(-1.0, 0.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
        Camera::mainCamera.rotate(0.01f, glm::vec3(0.0, 0.0, 1.0));
    } else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        Camera::mainCamera.globalTranslate(glm::vec3(0.0, 1.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(0.0, 1.0, 0.0) * 0.01f;
        // cout << Camera::mainCamera.position.x << ", " << Camera::mainCamera.position.y << ", "
        //      << Camera::mainCamera.position.z << endl;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
        Camera::mainCamera.globalTranslate(glm::vec3(0.0, -1.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(0.0, -1.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
        Camera::mainCamera.globalTranslate(glm::vec3(1.0, 0.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(1.0, 0.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
        Camera::mainCamera.globalTranslate(glm::vec3(-1.0, 0.0, 0.0) * 0.01f);
        // Camera::mainCamera.position += glm::vec3(-1.0, 0.0, 0.0) * 0.01f;
        // Camera::mainCamera.recalculate();
    } else if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
        Camera::mainCamera.rotate(-0.01f, glm::vec3(0.0, 0.0, 1.0));
    } else if (key == GLFW_KEY_Y && action == GLFW_REPEAT) {
        Camera::mainCamera.scale(glm::vec3(1.01, 1.01, 1.0));
    } else if (key == GLFW_KEY_H && action == GLFW_REPEAT) {
        Camera::mainCamera.scale(glm::vec3(0.99, 0.99, 1.0));
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int load_shaders() {
    // create a simple vertex shader
    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "out vec4 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "  vertexColor = vec4(aColor, 1.0);\n"
                                     "}\0";

    // define vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // bind code and compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Fragment shader
    const char *fragmentShaderSource = "#version 460 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec4 vertexColor;\n"
                                       "uniform vec4 ourColor;\n"
                                       "void main() {\n"
                                       //    "    FragColor = ourColor;\n"
                                       "    FragColor = vertexColor;\n"
                                       "};\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // SHADER PROGRAM
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    return shaderProgram;
}

unsigned int create_texture(const char *imagePath) {
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // // // Border color
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    // // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // // Setting interpolation options
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // Mipmaps interpolation
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data) {
        unsigned int len = strlen(imagePath);
        GLint format = GL_RGBA;
        if (strcmp(&imagePath[len - ENDING], ".jpg") == 0) {
            format = GL_RGB;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}