#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Window.h>
#include <Shader.h>
#include <Image.h>

#include <cmath>

int main() {
    LearnOpenGL::Window window(800, 600, "Transformation");

    const GLfloat vertices[]{
        //   positions    texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
    };

    const GLuint indices[]{
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    LearnOpenGL::Shader shader("res/shaders/Transformation/vertex.glsl",
                               "res/shaders/Transformation/fragment.glsl");

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    GLuint texture1, texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    LearnOpenGL::Image image("res/textures/container.jpg");

    if (image.genTexImage2D(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE)) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image.load("res/textures/awesomeface.png");
    if (image.genTexImage2D(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    shader.use();
    shader.set("texture1", 0);
    shader.set("texture2", 1);

    while (!window.isWindowShouldClose()) {
        if (window.isPressed(GLFW_KEY_ESCAPE)) window.close();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, {0.1f, -0.1f, 0.0f});
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), {0.0f, 0.0f, 1.0f});

        shader.use();
        glUniformMatrix4fv(shader.getUniformLocation("trans"), 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.updateFrame();
    }

    glfwTerminate();
}
