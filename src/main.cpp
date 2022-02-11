// #define GLEW_STATIC
#include "functions.hpp"
#include "math.h"
#include "shaders.hpp"

using namespace std;

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

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

    // Set blend tex as uint 1.
    ourShader.use();
    ourShader.setInt("blendTex", 1);
    ourShader.setInt("normalTex", 2);

    // unsigned int shaderProgram = load_shaders();
    // glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(.0f, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // cout << greenValue << endl;
        // int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
        ourShader.use();
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        ourShader.setFloat("time", greenValue);
        ourShader.setFloat("offset", greenValue);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mainTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, blendTex);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, normalTex);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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