#include <iostream>
#include <chrono>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Material.h"
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "DynMat.h"
#include "Lambertian.h"
#include "Glass.h"
#include <thread>
#include "Triangle.h"

constexpr int WIDTH = 1280, HEIGHT = 720, MAX_BOUNCES = 4, SPP = 16;

int* pixels;

void display(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
//    glFlush();
    glutSwapBuffers();
}

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
    Texture t = Texture(p);
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);

    world.addShape(new Triangle(Vector3(0, -6, 0), Vector3(3, -6, 0), Vector3(0, 0, 0), new Lambertian(Texture(1, 1, 1), Vector3(1, 1, 1))));

//    world.addShape(new Sphere(Vector3(0, -2, 5), 2, new Glass(1.5f)));
//    world.addShape(new Sphere(Vector3(0, -4, 0), 4, new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));
//    world.addShape(new Sphere(Vector3(0, 0, 2), 5, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));
//    world.addShape(new Sphere(Vector3(-5, 0, 2), 4, new DynMat(0, 1, Texture(1, 0.7, 0.1))));
//    world.addShape(new Sphere(Vector3(5, -2, 2), 2, new DynMat(0.06, 0.5, Texture(), Vector3(1, 0.7, 0.1))));
    world.addShape(new Sphere(Vector3(0, -1006, 0), 1000, new Lambertian(Texture(Texture::CHECKERBOARD, Vector3(0, 0, 0), Vector3(1, 1, 1)))));
//    world.addShape(new Sphere(Vector3(0, -1006, -1), 1000, new DynMat(0, 0.6, Texture(1, 1, 1))));
//    world.addShape(new Triangle(Vector3(2.0,1.0,3.0), Vector3(5.0,2.0,3.0), Vector3(1.0,3.0,5.0), new DynMat(0, 0, Texture(0.0, 0.0, 0.0), Vector3(0, 0.9, 0.9))));
//    world.addShape(new Triangle(Vector3(5.0,2.0,3.0),Vector3(1.0,3.0,5.0), Vector3(2.0,1.0,3.0),  new DynMat(0, 0, Texture(0.0, 0.0, 0.0), Vector3(0, 0.9, 0.9))));

    std::thread renderThread(renderAsync, std::ref(world));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1920.0f / 2.0f - WIDTH / 2.0f, 1080.0f / 2.0f - HEIGHT / 2.0f);
    glutCreateWindow("Path Tracer");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    renderThread.join();
    return 0;
}