#ifndef _LEARN_OPENGL_WINDOW_H_
#define _LEARN_OPENGL_WINDOW_H_
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

namespace LearnOpenGL {
    class Window {
       public:
        Window(int width = 640, int height = 480, const char *title = nullptr,
               bool centered = true) {
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
            glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
            window = glfwCreateWindow(width, height, title, nullptr, nullptr);

            if (!window) {
                std::cerr << "Failed to create glfw window" << std::endl;
                glfwTerminate();
                std::exit(0);
            }

            if (centered) {
                const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                glfwSetWindowPos(window, (vidmode->width - width) / 2,
                                 (vidmode->height - height) / 2);
            }
            glfwMakeContextCurrent(window);

            glfwShowWindow(window);
        }

        GLFWwindow *getHandle() { return window; }

        GLFWwindow *getHandle() const { return window; }

        bool shouldClose() const { return glfwWindowShouldClose(window); }

       protected:
        GLFWwindow *window;
    };
}  // namespace LearnOpenGL
#endif