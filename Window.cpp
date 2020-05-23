//
// Created by legend on 4/26/20.
//

#include "Window.h"

#include <iostream>

Window::Window(int width, int height, int* pixels) : width(width), height(height), pixels(pixels) {
    // OpenGL stuff
    if(!glfwInit())
        std::cerr << "Failed to initialize GLFW, is it installed?" << std::endl;
    window = glfwCreateWindow(width, height, "Path Tracer", NULL, NULL);
    if(!window) {
        glfwTerminate();
        std::cerr << "Failed to created GLFW window, issue with GLFW installation?" << std::endl;
    }
    glfwMakeContextCurrent(window);
}

Window::~Window(){
    glfwTerminate();
}

void Window::start() const {
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}