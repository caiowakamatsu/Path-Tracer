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

constexpr int WIDTH = 1024, HEIGHT = 576, MAX_BOUNCES = 6, SPP = 16 ;

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
    const char* p = "../skybox/abandoned_parking.jpg";
//    const char* p = "../skybox/modern_buildings_night.jpg";
//    const char* p = "../skybox/kloofendal_48d_partly_cloudy.jpg";
//    const char* p = "../skybox/shanghai_bund.jpg";
//    const char* p = {"../skybox/adams_place_bridge.jpg"};
    pixels = new int[WIDTH * HEIGHT]{0};
    Texture t = Texture(p, .875, 0);
//    Texture t = Texture();
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);

    std::vector<Vector3> offsets = {};
//    offsets.emplace_back(0, 0, 6);
//    offsets.emplace_back(0, 0, 0);
//    offsets.emplace_back(0, 0, -6);
    world.loadModel("../models/lowpoly/rabbit.obj");

    world.setCameraLocation(Vector3(5, 5, 5));
    Window window(WIDTH, HEIGHT, pixels);
    std::thread renderThread(renderAsync, std::ref(world));
    window.start();
    renderThread.join();
    delete(pixels);
    return 0;
}