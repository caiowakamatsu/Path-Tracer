#include <iostream>
#include <chrono>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Material.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "DynMat.h"
#include "Lambertian.h"
#include "Glass.h"
#include <thread>
#include "Triangle.h"
#include "Rectangle.h"
#include "NormalMat.h"

constexpr int WIDTH = 1280, HEIGHT = 720, MAX_BOUNCES = 8, SPP = 32;

int* pixels;

void renderAsync(World& world){
    auto start = std::chrono::high_resolution_clock::now();
    world.render(pixels, 16);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    printf("Total Execution Time %.2fms\n",
           std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / 1000000.0f);
}

int main(int argc, char **argv) {

    const char* p = "../skybox/abandoned_parking.jpg";
//    const char* p = "../skybox/modern_buildings_night.jpg";
//    const char* p = "../skybox/kloofendal_48d_partly_cloudy.jpg";
//    const char* p = "../skybox/shanghai_bund.jpg";
//    const char* p = {"../skybox/adams_place_bridge.jpg"};
    pixels = new int[WIDTH * HEIGHT]{0};
    Texture t = Texture(p, .875, 0);
//    Texture t = Texture();
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);

        Vector3 translation(0, 0, -20);
        Vector3 size(19, 20, 19);

        int scale = 2;

//        world.addShape(
//                new Triangle(
//                        Vector3(20, -5, 0) + translation,
//                        Vector3(20, -5, -20) + translation,
//                        Vector3(-20, -5, 0) + translation,
//                        new Lambertian(Texture(.7, .7, .7))
//                        ));

//         Bottom floor
        scale *= 3;
//        world.addShape(
//            new Rectangle(
//                    Vector3(-(size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
//                    Vector3(-(size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
//                    Vector3((size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
//                    Vector3((size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
//                    new DynMat(0, 1, Texture(1, 1, 1))));

//        world.addShape(
//                new Triangle(
//                        Vector3(10, -10, 10),
//                        Vector3(10, -10, -10),
//                        Vector3(-10, -10, 10),
//                        new DynMat(0, 1, Texture(1, 1, 1))));

        world.addShape(
                new Rectangle(
                        Vector3((size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
                        Vector3((size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
                        Vector3(-(size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
                        Vector3(-(size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
//                        new DynMat(0, 1, Texture(1, 1, 1))));
//                        new Glass(1.5f)));
                        new Lambertian(Texture(0.7, 0.7, 0.7))));
//                        new NormalMat(true)));1 thoidk


//        world.addShape(new Sphere(Vector3(0, -1010, 0), 1000, new DynMat(0, 1, Texture(1, 1, 1))));

        scale /=3;

        world.addShape(new Sphere(Vector3(0, 0, 0) + translation, 5, new NormalMat(true)));

        world.addShape(
                new Rectangle(
                        Vector3((-size.x / 2) * scale, size.y / 2, (size.z / 2) * scale) + translation,
                        Vector3((-size.x / 2) * scale, size.y / 2, (-size.z / 2) * scale) + translation,
                        Vector3((size.x / 2) * scale, size.y / 2, (size.z / 2) * scale) + translation,
                        Vector3((size.x / 2) * scale, size.y / 2, (-size.z / 2) * scale) + translation,
//                        new Lambertian(Texture(0.7, 0.7, 0.7))));
//                        new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));
                        new Lambertian(Texture(), Vector3(1, 1, 1))));

//    int size = 5;
//    int start = -1 * (size-1) / 2;
//    int end = size + start;
//    for(int x=start; x<end; x++)
//        for(int y=start; y<end; y++)
//            for(int z=start; z<end; z++){
//                Material* mat;
//                if(drand48() < 0.5){
//                    mat = new Glass(1.5);
//                } else {
//                    mat = new DynMat(0, 1, Texture(drand48() * 0.5 + 0.5, drand48() * 0.5 + 0.5, drand48() * 0.5 + 0.5));
//                }
//                world.addShape(new Sphere(Vector3(x * 7 + drand48() * 2.5, y * 7 + drand48() * 2.5, z * 7 + drand48() * 2.5), drand48() * 2 + 1, mat));
//            }


    GLFWwindow* window;

    if(!glfwInit()){ // I should really make a window class to make this code somewhat cleaner...
        std::cerr << "Failed to initialize GLFW, is it installed?" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "Path Tracer", NULL, NULL);
    if(!window){
        glfwTerminate();
        std::cerr << "Failed to created GLFW window, issue with GLFW installation?" << std::endl;
        return -1;
    }

    std::thread renderThread(renderAsync, std::ref(world));

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    renderThread.join();
    delete(pixels);
    return 0;
}