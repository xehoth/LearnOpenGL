#ifndef _LEARN_OPENGL_UTILS_H_
#define _LEARN_OPENGL_UTILS_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

namespace LearnOpenGL {
    // default glfw init
    void defaultInit();

    // load glad
    void loadOpenGL();

    /**
     * get the best monitor
     * @param window glfw window
     * @return the monitor
     */
    GLFWmonitor *getBestMonitor(GLFWwindow *window);
}  // namespace LearnOpenGL

// implement

namespace LearnOpenGL {
    void defaultInit() {
        static bool hasInit = false;
        if (hasInit) return;
        hasInit = true;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    void loadOpenGL() {
        static bool hasLoaded = false;
        if (hasLoaded) return;
        hasLoaded = true;
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to init glad" << std::endl;
            exit(-1);
        }
    }

    GLFWmonitor *getBestMonitor(GLFWwindow *window) {
        int monitorCount;
        GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

        if (!monitors) return nullptr;

        int windowX, windowY, windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glfwGetWindowPos(window, &windowX, &windowY);

        GLFWmonitor *bestMonitor = nullptr;
        int bestArea = 0;

        for (int i = 0; i < monitorCount; ++i) {
            GLFWmonitor *monitor = monitors[i];

            int monitorX, monitorY;
            glfwGetMonitorPos(monitor, &monitorX, &monitorY);

            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            if (!mode) continue;

            int areaMinX = std::max(windowX, monitorX);
            int areaMinY = std::max(windowY, monitorY);

            int areaMaxX = std::min(windowX + windowWidth, monitorX + mode->width);
            int areaMaxY = std::min(windowY + windowHeight, monitorY + mode->height);

            int area = (areaMaxX - areaMinX) * (areaMaxY - areaMinY);

            if (area > bestArea) {
                bestArea = area;
                bestMonitor = monitor;
            }
        }

        return bestMonitor;
    }
}  // namespace LearnOpenGL
#endif