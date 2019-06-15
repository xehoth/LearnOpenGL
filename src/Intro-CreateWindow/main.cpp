#include <glad/glad.h>
#include <Window.h>

#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    LearnOpenGL::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(
        window.getHandle(),
        [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

    while (!window.shouldClose()) {
        if (glfwGetKey(window.getHandle(), GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window.getHandle(), true);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.getHandle());
        glfwPollEvents();
    }

    glfwTerminate();
}