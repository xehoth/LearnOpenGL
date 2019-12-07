#include <Window.h>
#include <iostream>

int main() {
    LearnOpenGL::Window window(1920, 1080);

    while (!window.isWindowShouldClose()) {
        if (window.isPressed(GLFW_KEY_ESCAPE)) window.close();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.updateFrame();
    }
    glfwTerminate();
}
