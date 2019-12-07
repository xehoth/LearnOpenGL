#include <Window.h>
#include <Shader.h>
#include <cmath>

int main() {
    LearnOpenGL::Window window(800, 600, "Shader");

    const GLfloat vertices[]{
        //   position            color
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
    };

    LearnOpenGL::Shader shader("res/shaders/Shader/vertex.glsl",
                               "res/shaders/Shader/fragment.glsl");

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position -> 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // color -> 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    while (!window.isWindowShouldClose()) {
        if (window.isPressed(GLFW_KEY_ESCAPE)) window.close();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.set("r", std::abs(sinf(static_cast<float>(glfwGetTime()))));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.updateFrame();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
}
