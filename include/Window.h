#ifndef _LEARN_OPENGL_WINDOW_H_
#define _LEARN_OPENGL_WINDOW_H_
#include <Utils.h>
#include <iostream>
#include <cstdlib>
#include <functional>

namespace LearnOpenGL {
    constexpr auto DEFAULT_FRAMEBUFFER_SIZE_CALLBACK =
        [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); };

    class Window final {
       public:
        Window(int width, int height, const char *title, bool centered);

        GLFWwindow *getHandle() { return window; }
        GLFWwindow *getHandle() const { return window; }

        bool isWindowShouldClose() const { return glfwWindowShouldClose(window); }

        void setFramebufferSizeCallback(
            void (*func)(GLFWwindow *, int, int) = DEFAULT_FRAMEBUFFER_SIZE_CALLBACK) const {
            glfwSetFramebufferSizeCallback(window, func);
        }

        bool isPressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

        void close() const { glfwSetWindowShouldClose(window, true); }

        void updateFrame() const {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

       private:
        GLFWwindow *window;
    };
}  // namespace LearnOpenGL

// implement

namespace LearnOpenGL {
    Window::Window(int width, int height, const char *title = "", bool centered = true) {
        defaultInit();
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!window) {
            std::cerr << "Failed to create glfw window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        if (centered) {
            const GLFWvidmode *vidmode = glfwGetVideoMode(getBestMonitor(window));
            glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
        }
        glfwMakeContextCurrent(window);
        glfwShowWindow(window);
        loadOpenGL();
    }

}  // namespace LearnOpenGL

#endif