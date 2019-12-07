#include <Window.h>
#include <Shader.h>

using LearnOpenGL::Shader;

int main() {
    LearnOpenGL::Window window(1920, 1080, "Intro-Triangle");
    Shader shader("res/shaders/Triangle/vertex.glsl", "res/shaders/Triangle/fragment.glsl");

    const GLfloat vertices[]{
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };

    GLuint indices[]{
        0, 1, 3,  // first
        1, 2, 3   // second
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    auto processInput = [&] {
        if (window.isPressed(GLFW_KEY_L)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (window.isPressed(GLFW_KEY_F)) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (window.isPressed(GLFW_KEY_ESCAPE)) window.close();
    };

    while (!window.isWindowShouldClose()) {
        processInput();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.updateFrame();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
}