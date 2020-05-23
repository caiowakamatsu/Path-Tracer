#include <iostream>
#include <chrono>
#include "World.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <thread>
#include "Window.h"
#include "DynMat.h"
#include "Lambertian.h"
#include "Glass.h"

constexpr int WIDTH = 1024, HEIGHT = 576, MAX_BOUNCES = 6, SPP = 64;

//#define SPHERES

int* pixels;

void renderAsync(World& world){
    world.buildBvh();
    auto start = std::chrono::high_resolution_clock::now();
    world.render(pixels, 14);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    printf("Total Execution Time %.2fms\n",
           std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / 1000000.0f);
}

int main(int argc, char **argv) {
//    const char* p = "../skybox/abandoned_parking.jpg";
//    const char* p = "../skybox/modern_buildings_night.jpg";
//    const char* p = "../skybox/kloofendal_48d_partly_cloudy.jpg";
//    const char* p = "../skybox/shanghai_bund.jpg";
    const char* p = {"../skybox/adams_place_bridge.jpg"};
    pixels = new int[WIDTH * HEIGHT]{0};
//    Texture t = Texture(p, .875, 0);
    Texture t = Texture();
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);

    std::vector<Vector3> offsets = {};
    offsets.emplace_back(0, 0, 6);
    offsets.emplace_back(0, 0, 0);
    offsets.emplace_back(0, 0, -6);
//    world.loadObj("../objs/fox.obj", new DynMat(0, 1, Texture("../objs/texture.png")), offsets);
//    world.loadObj("../objs/dragon.obj", new Lambertian(Texture(0.7, 0.7, 0.7)), offsets);
    world.loadObj("../objs/dragon.obj", new Glass(1.5f), offsets);
//    world.loadObj("../objs/utah-teapot.obj", new DynMat(0, 1, Texture(1, 1, 1)), offsets);
    world.addTriangle(new Triangle(
            Vertex(Vector3(2, 15, 2)),
            Vertex(Vector3(-2, 15, 2)),
            Vertex(Vector3(2, 15, -2)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(.5, .5, .5))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(-2, 15, -2)),
            Vertex(Vector3(-2, 15, 2)),
            Vertex(Vector3(2, 15, -2)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(.5, .5, .5))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(1, 4, 16)),
            Vertex(Vector3(5, 4, 16)),
            Vertex(Vector3(5, 9, 14)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(0, .7, .7))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(1, 4, 16)),
            Vertex(Vector3(1, 9, 14)),
            Vertex(Vector3(5, 9, 14)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(0, .7, .7))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(1, 4, -16)),
            Vertex(Vector3(5, 4, -16)),
            Vertex(Vector3(5, 9, -14)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(0.63,0.13,0.94))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(1, 4, -16)),
            Vertex(Vector3(1, 9, -14)),
            Vertex(Vector3(5, 9, -14)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(0.63,0.13,0.94))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(-15, 4, 1)),
            Vertex(Vector3(-13, 9, 1)),
            Vertex(Vector3(-13, 9, 5)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(1., .1, .1))));

    world.addTriangle(new Triangle(
            Vertex(Vector3(-15, 4, 1)),
            Vertex(Vector3(-15, 4, 5)),
            Vertex(Vector3(-13, 9, 5)), new DynMat(0, 0, Texture(1, 1, 1), Vector3(1., .1, .1))));


    world.setCameraLocation(Vector3(-20, 20, 20));
    Window window(WIDTH, HEIGHT, pixels);
    std::thread renderThread(renderAsync, std::ref(world));
    window.start();
    renderThread.join();
    delete(pixels);
    return 0;
}