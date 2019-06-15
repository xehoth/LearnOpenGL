#include <glad/glad.h>

#include <Window.h>
#include <Shader.h>
#include <Image.h>

#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void processInput(const LearnOpenGL::Window &);

int main() {
    LearnOpenGL::Window::defaultInit();
    LearnOpenGL::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL");
    LearnOpenGL::Window::loadOpenGL();

    const GLfloat vertices[]{
        //     positions         colors     texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };

    const GLuint indices[]{
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    LearnOpenGL::Shader shader("vertex2.glsl", "fragment2.glsl");

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    GLuint texture1, texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    LearnOpenGL::Image image("container.jpg");

    if (image.genTexImage2D(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE)) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image.load("awesomeface.png");
    if (image.genTexImage2D(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    shader.use();
    shader.set("texture1", 0);
    shader.set("texture2", 1);

    while (!window.shouldClose()) {
        processInput(window);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();
        shader.set("r", std::abs(std::sinf((float)glfwGetTime())));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.updateFrame();
    }

    glfwTerminate();
}

void processInput(const LearnOpenGL::Window &window) {
    if (window.isPressed(GLFW_KEY_ESCAPE)) {
        window.setWindowShouldClose();
    }
}