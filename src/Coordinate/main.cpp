#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Window.h>
#include <Shader.h>
#include <Image.h>

#include <cmath>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    LearnOpenGL::Window window(SCR_WIDTH, SCR_HEIGHT, "Coordinate");
    glEnable(GL_DEPTH_TEST);

    const GLfloat vertices[]{
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  //
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  //
                                          //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     //
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,    //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
                                          //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
                                          //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,   //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,   //
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
                                          //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
                                          //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,    //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f    //
    };

    const glm::vec3 cubePositions[]{
        {0.0f, 0.0f, 0.0f},      //
        {2.0f, 5.0f, -15.0f},    //
        {-1.5f, -2.2f, -2.5f},   //
        {-3.8f, -2.0f, -12.3f},  //
        {2.4f, -0.4f, -3.5f},    //
        {-1.7f, 3.0f, -7.5f},    //
        {1.3f, -2.0f, -2.5f},    //
        {1.5f, 2.0f, -2.5f},     //
        {1.5f, 0.2f, -1.5f},     //
        {-1.3f, 1.0f, -1.5f}     //
    };

    LearnOpenGL::Shader shader("res/shaders/Coordinate/vertex.glsl",
                               "res/shaders/Coordinate/fragment.glsl");

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    auto genTexture = [](const char *path, GLenum format) {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        LearnOpenGL::Image image(path);
        if (image.genTexImage2D(GL_RGB, format, GL_UNSIGNED_BYTE)) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        return tex;
    };

    GLuint texture1 = genTexture("res/textures/container.jpg", GL_RGB);
    GLuint texture2 = genTexture("res/textures/awesomeface.png", GL_RGBA);

    auto getDisInputUpdate = [&](float dis) {
        return [dis, &window]() mutable {
            if (window.isPressed(GLFW_KEY_DOWN)) dis -= 0.01f;
            if (window.isPressed(GLFW_KEY_UP)) dis += 0.01f;
            return dis;
        };
    };

    auto updateDis = getDisInputUpdate(-3.0f);

    shader.use();
    shader.set("texture1", 0);
    shader.set("texture2", 1);

    while (!window.isWindowShouldClose()) {
        if (window.isPressed(GLFW_KEY_ESCAPE)) window.close();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();

        glm::mat4 model(1.0f), view(1.0f), projection(1.0f);
        view = glm::translate(view, {0.0f, 0.0f, updateDis()});
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);

        shader.set("view", view);
        shader.set("projection", projection);

        glBindVertexArray(vao);
        for (int i = 0; i < 10; i++) {
            model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i + (float)glfwGetTime() * 5.0f),
                                {1.0f, 0.3f, 0.5f});
            shader.set("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        window.updateFrame();
    }
    glfwTerminate();
}