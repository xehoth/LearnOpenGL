#include <glad/glad.h>
#include <Window.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    LearnOpenGL::Window::defaultInit();
    LearnOpenGL::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Intro-Triangle");
    LearnOpenGL::Window::loadOpenGL();
    window.setFramebufferSizeCallback();

    while (!window.shouldClose()) {
        if (window.isPressed(GLFW_KEY_ESCAPE)) {
            window.setWindowShouldClose();
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.updateFrame();
    }

    glfwTerminate();
}