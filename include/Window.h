#ifndef _LEARN_OPENGL_WINDOW_H_
#define _LEARN_OPENGL_WINDOW_H_
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <functional>

namespace LearnOpenGL {
    constexpr auto DEFAULT_FRAMEBUFFER_SIZE_CALLBACK =
        [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); };

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

        static void defaultInit() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        }

        static void loadOpenGL() {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to init glad" << std::endl;
                std::exit(0);
            }
        }

        void setFramebufferSizeCallback(void (*func)(GLFWwindow *window, int width, int height) =
                                            DEFAULT_FRAMEBUFFER_SIZE_CALLBACK) const {
            glfwSetFramebufferSizeCallback(window, func);
        }

        bool isPressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

        void setWindowShouldClose() const { glfwSetWindowShouldClose(window, true); }

        void updateFrame() const {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

       protected:
        GLFWwindow *window;
    };
}  // namespace LearnOpenGL

#endif