//
// Created by legend on 4/26/20.
//

#pragma once

#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* window;
    int width, height, *pixels;
public:
    Window(int width, int height, int* pixels);
    ~Window();

    void start() const;
};
