#include <iostream>
#include <chrono>
#include <cstddef>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "DynMat.h"
#include "Lambertian.h"

constexpr int WIDTH = 1280, HEIGHT = 720, MAX_BOUNCES = 2, SPP = 16;

int* pixels;

void display(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glFlush();
}


int main(int argc, char **argv) {

//    const char* p = "../skybox/abandoned_parking.jpg";
//    const char* p = "../skybox/modern_buildings_night.jpg";
//    const char* p = "../skybox/shanghai_bund.jpg";
    const char* p = {"../skybox/adams_place_bridge.jpg"};
    Texture t = Texture(p);
    pixels = new int[WIDTH * HEIGHT]{0};
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);
    world.addShape(new Sphere(Vector3(5, 0, -1), 5, new Lambertian(Texture(1, 1, 1))));
    world.addShape(new Sphere(Vector3(-3, 0, -1), 2, new DynMat(0.01, 0.2, Texture(1, 1, 1))));
//    world.addShape(new Sphere(Vector3(0, -1006, -1), 1000, new DynMat(0.01, 0.2, Texture(1, 1, 1))));
//    world.addShape(new Sphere(Vector3(-8, 0, -1), 7, new DynMat(0, 1, Texture(1, 0.8f, 0.6f))));
//    world.addShape(new Sphere(Vector3(8, 0, -1), 7, new DynMat(0, 1, Texture(0.6f,1,1))));

    auto start = std::chrono::high_resolution_clock::now();
    world.render(pixels);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    printf("Total Execution Time %.2fms\n",
            std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / 1000000.0f);


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1920.0f / 2.0f - WIDTH / 2.0f, 1080.0f / 2.0f - HEIGHT / 2.0f);
    glutCreateWindow("Path Tracer");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}