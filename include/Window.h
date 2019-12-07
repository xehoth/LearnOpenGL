#ifndef _LEARN_OPENGL_WINDOW_H_
#define _LEARN_OPENGL_WINDOW_H_
#include <Utils.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <string>

namespace LearnOpenGL {
    class Window final {
       public:
        Window(int width, int height, const std::string &title, bool centered);

        GLFWwindow *getHandle() { return window; }
        GLFWwindow *getHandle() const { return window; }

        bool isWindowShouldClose() const { return glfwWindowShouldClose(window); }

        bool isPressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

        void close() const { glfwSetWindowShouldClose(window, true); }

        const std::string &getTitle() const { return title; }

        void setTitle(const std::string &title) {
            this->title = title;
            glfwSetWindowTitle(window, title.c_str());
        }

        inline void showFPS() const;

        void updateFrame() const {
            showFPS();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

       private:
        GLFWwindow *window;
        std::string title;
    };
}  // namespace LearnOpenGL

// implement

namespace LearnOpenGL {
    Window::Window(int width, int height, const std::string &title = "", bool centered = true)
        : title(title) {
        defaultInit();
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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

    inline void Window::showFPS() const {
        // Measure speed
        static double lastTime;
        static int frames;
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        frames++;
        if (delta >= 1.0) {  // If last count was more than 1 sec ago
            double fps = frames / delta;
            glfwSetWindowTitle(window, (title + " [" + std::to_string(fps) + " FPS]").c_str());
            frames = 0;
            lastTime = currentTime;
        }
    }

}  // namespace LearnOpenGL

#endif