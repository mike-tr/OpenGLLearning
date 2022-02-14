// #define GLEW_STATIC
#include "camera.hpp"
#include "etime.hpp"
#include "gameObject.hpp"
#include "math.h"
#include "shaders.hpp"
#include <iomanip>

using namespace std;

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    cout << glGetString(GL_VERSION) << endl;

    // DRAW A RECTANGLE

    // create vertex data
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // create object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // // set object as GL_ARRAYP_BUFFER
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // // bind vertices to the object
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell how to draw the data.
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // indicies object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // load shaders
    // unsigned int shaderProgram = load_shaders();
    // glUseProgram(shaderProgram);

    // Generate a vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // copy indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. then set our vertex attributes pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // position attribute
    // the first value is the arrtibute array i.e location = 0, the second is the vector length in this case 3.
    // then the type, and if its need to be notmalized, next the size of each "block", in this case we have 6 values.
    // last the offset, so to get position we start at index 0, as for colors we start from 3.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader ourShader = Shader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
    unsigned int mainTex = create_texture("assets/images/brick.jpg");
    unsigned int blendTex = create_texture("assets/images/rabbit.jpg");
    unsigned int normalTex = create_texture("assets/images/normalmap.jpg");
    unsigned int mainTex2 = create_texture("assets/images/skeletor.jpg");
    // Set blend tex as uint 1.
    ourShader.use();
    ourShader.setInt("blendTex", 1);
    ourShader.setInt("normalTex", 2);

    // unsigned int shaderProgram = load_shaders();
    // glUseProgram(shaderProgram);
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // glm::mat4 trans = glm::mat4(1.0f);
    // // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    // vec = trans * vec;
    vec = vec + vec;
    vec.y += 1;
    std::cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << std::endl;

    unsigned int cube = create_cube_bad();
    unsigned int cubeb = create_cube();

    Material mat = Material(ourShader);
    GameObject obj[] = {GameObject(cube, 36, false, mat), GameObject(cube, 36, false, mat), GameObject(cubeb, 36, true, mat)};

    obj[0].setPosition(glm::vec3(0.5f, -0.5f, -2.0f));
    obj[0].localScale(glm::vec3(1.0f, 1.0f, 1.0f) * 0.5f);
    obj[0].rotate(0.1, glm::vec3(0.0, 0.0, 1.0));

    obj[1].setPosition(glm::vec3(0.5f, 0.5f, -1.0f));
    obj[1].localScale(glm::vec3(1.0f, 1.0f, 1.0f) * 0.33f);
    obj[1].rotate(-0.1, glm::vec3(0.0, 0.0, 1.0));

    obj[2].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    obj[2].localScale(glm::vec3(1.0f, 1.0f, 1.0f) * 0.1f);

    for (unsigned int i = 0; i < 3; i++) {
        obj[i].getMaterial().setFloat("time", 1);
        obj[i].getMaterial().setFloat("offset", 1);
        obj[i].getMaterial().setTexture("mainTex", 0, mainTex);
        obj[i].getMaterial().setTexture("blendTex", 1, blendTex);
        obj[i].getMaterial().setTexture("normalTex", 2, normalTex);
    }

    obj[2].getMaterial().setTexture("blendTex", 1, mainTex2);
    obj[1].getMaterial().setTexture("blendTex", 1, normalTex);

    glEnable(GL_DEPTH_TEST);
    cout << "start while" << endl;
    Camera::mainCamera.lookAt(glm::vec3(0.0, 0.0, 0.0));

    ETime::update();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        ETime::update();
        processInput(window);
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < 3; i++) {
            glm::vec3 t = glm::vec3(0.001 * (1 - i), 0.001 * (2 - i), 0.0);
            if (i != 2) {
                obj[i].localTranslate(t);
            }
            glm::vec3 axis = glm::vec3(0.0, 0.0, 0.0);
            if (i == 0) {
                axis.x = sqrt(2);
                axis.y = sqrt(2);
            } else if (i == 1) {
                axis.y = 1;
            } else {
                axis.x = -sqrt(2);
                axis.z = sqrt(2);
            }
            obj[i].rotate(0.005 * (i + 1), axis);
            obj[i].draw(Camera::mainCamera);
        }
        // obj[1].draw(Camera::mainCamera);
        // obj[2].draw(Camera::mainCamera);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}