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
#include "Rectangle.h"
#include "NormalMat.h"

constexpr int WIDTH = 1280, HEIGHT = 720, MAX_BOUNCES = 8, SPP = 64;

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

//    const char* p = "../skybox/abandoned_parking.jpg";
//    const char* p = "../skybox/modern_buildings_night.jpg";
//    const char* p = "../skybox/kloofendal_48d_partly_cloudy.jpg";
//    const char* p = "../skybox/shanghai_bund.jpg";
    const char* p = {"../skybox/adams_place_bridge.jpg"};
    pixels = new int[WIDTH * HEIGHT]{0};
    Texture t = Texture();
    auto world = World(WIDTH, HEIGHT, t, MAX_BOUNCES, SPP);

        Vector3 translation(0, 0, -5);
        Vector3 size(19, 24, 19);

        int scale = 2;

//         Bottom floor
//        world.addShape(
//                new Rectangle(
//                        Vector3((size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
//                        Vector3((size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
//                        Vector3(-(size.x / 2) * scale, -size.y / 2, (size.z / 2) * scale) + translation,
//                        Vector3(-(size.x / 2) * scale, -size.y / 2, -(size.z / 2) * scale) + translation,
//                        new NormalMat(true)));

        world.addShape(
                new Sphere(Vector3(0, -10005, 0) + translation, 10000,
//                        new Lambertian(Texture(0.7, 0.7, 0.7)))
                        new NormalMat(true))
                );
//
//        world.addShape(
//                new Sphere(Vector3(0, -0, -5), 4, new DynMat(0, 1, Texture(1, 1, 1)))
//                );

        // Top ceiling
        world.addShape(
                new Rectangle(
                        Vector3(-size.x / 2, size.y / 2, size.z / 2) + translation,
                        Vector3(-size.x / 2, size.y / 2, -size.z / 2) + translation,
                        Vector3(size.x / 2, size.y / 2, size.z / 2) + translation,
                        Vector3(size.x / 2, size.y / 2, -size.z / 2) + translation,
//                        new Lambertian(Texture(0.7, 0.7, 0.7))));
                        new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));
//                        new Lambertian(Texture(), Vector3(1, 1, 1))));

/*
        // Back wall
        world.addShape(
                new Rectangle(
                        Vector3(-size.x / 2, size.y / 2, -size.z / 2) + translation,
                        Vector3(-size.x / 2, -size.y / 2, -size.z / 2) + translation,
                        Vector3(size.x / 2, size.y / 2, -size.z / 2) + translation,
                        Vector3(size.x / 2, -size.y / 2, -size.z / 2) + translation,
                        new Lambertian(Texture(0.7, 0.7, 0.7))));

        // Left wall
        world.addShape(
                new Rectangle(
                        Vector3(-size.x / 2, -size.y / 2, -size.z / 2) + translation,
                        Vector3(-size.x / 2, -size.y / 2, size.z / 2) + translation,
                        Vector3(-size.x / 2, size.y / 2, -size.z / 2) + translation,
                        Vector3(-size.x / 2, size.y / 2, size.z / 2) + translation,
                        new Lambertian(Texture(0.9, 0.1, 0.1))));

        // Right wall
        world.addShape(
                new Rectangle(
                        Vector3(size.x / 2, -size.y / 2, size.z / 2) + translation,
                        Vector3(size.x / 2, -size.y / 2, -size.z / 2) + translation,
                        Vector3(size.x / 2, size.y / 2, size.z / 2) + translation,
                        Vector3(size.x / 2, size.y / 2, -size.z / 2) + translation,
                        new Lambertian(Texture(0.1, 0.9, 0.1))));
*/
//        world.addShape(
//                new Triangle(
//                        Vector3(0, 0, 0) + translation,
//                        Vector3(0, 0, 0) + translation,
//                        Vector3(0, 0, 0) + translation,
//                        new Lambertian)
//                )

//        world.addShape(
//                new Sphere(
//                        Vector3(0, size.y / 2 + 19.5, 0), 20, new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));

//        // Top Light

        float lightScale = 12;

//        world.addShape(
//                new Rectangle(
//                        Vector3(-size.x / lightScale, size.y / 2 - 0.5f, size.z / lightScale) + translation,
//                        Vector3(-size.x / lightScale, size.y / 2 - 0.5f, -size.z / lightScale) + translation,
//                        Vector3(size.x / lightScale, size.y / 2 - 0.5f, size.z / lightScale) + translation,
//                        Vector3(size.x / lightScale, size.y / 2 - 0.5f, -size.z / lightScale) + translation,
//                        new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));

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
    delete(pixels);
    return 0;
}