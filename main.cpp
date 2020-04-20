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

constexpr int WIDTH = 1280, HEIGHT = 720, MAX_BOUNCES = 8, SPP = 512;

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

//    world.addShape(new Triangle(Vector3(0, -6, 0), Vector3(3, -6, 0), Vector3(0, 0, 0), new Lambertian(Texture(1, 1, 1), Vector3(1, 1, 1))));

//    world.addShape(new Sphere(Vector3(0, -2, 5), 2, new Glass(1.5f)));
//    world.addShape(new Sphere(Vector3(2, -4, 0), 4, new DynMat(0, 0, Texture(), Vector3(1, 1, 1))));
    world.addShape(new Sphere(Vector3(6, 0, 2), 4, new Glass(1.5)));
    world.addShape(new Sphere(Vector3(6, 9, 2), 2, new Lambertian(Texture(), Vector3(1, 1, 1))));
    world.addShape(new Sphere(Vector3(-6, 0, 2), 4, new Lambertian(Texture(0.7, 0.7, 0.7))));
    world.addShape(new Sphere(Vector3(-6, 9, 2), 2, new Lambertian(Texture(), Vector3(1, 1, 1))));
//    world.addShape(new Sphere(Vector3(0, -2, 4), 2, new DynMat(0.06, 0.5, Texture(), Vector3(1, 0.7, 0.1))));
    world.addShape(new Sphere(Vector3(10.5, -1, 7), 1.2, new Lambertian(Texture(), Vector3(0, 0.8, 0.9))));
    world.addShape(new Sphere(Vector3(-10.5, -1, 7), 1.2, new Lambertian(Texture(), Vector3(0.9, 0.5, 0.2))));
//    world.addShape(new Sphere(Vector3(0, -1006, 0), 1000, new Lambertian(Texture(Texture::CHECKERBOARD, Vector3(0, 0, 0), Vector3(1, 1, 1)))));
    world.addShape(new Sphere(Vector3(0, -1006, -1), 1000, new DynMat(0.8, 0.6, Texture(1, 1, 1))));
    world.addShape(new Sphere(Vector3(0, 0, -1020), 1000, new DynMat(0, 1, Texture(1, 1, 1))));
//    world.addShape(new Triangle(Vector3(2.0,1.0,3.0), Vector3(5.0,2.0,3.0), Vector3(1.0,3.0,5.0), new DynMat(0, 0, Texture(0.0, 0.0, 0.0), Vector3(0, 0.9, 0.9))));
//    world.addShape(new Triangle(Vector3(-1.0,-5,0),Vector3(-1,-5,-2), Vector3(1.0,-5.0,0),  new DynMat(0, 0, Texture(0.0, 0.0, 0.0), Vector3(0, 0.9, 0.9))));
//    world.addShape(new Triangle(Vector3(-1.0,-7,0),Vector3(-1,-7,-2), Vector3(1.0,-7.0,0),  new DynMat(0, 0, Texture(0.0, 0.0, 0.0), Vector3(0.9, 0.9, 0.0))));


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
//    world.addShape(new Sphere(Vector3(0, -10, 0), 2, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));
//    world.addShape(new Sphere(Vector3(0, -5, 0), 2, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));
//    world.addShape(new Sphere(Vector3(0, 0, 0), 2, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));
//    world.addShape(new Sphere(Vector3(0, 5, 0), 2, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));
//    world.addShape(new Sphere(Vector3(0, 10, 0), 2, new DynMat(0, 1, Texture(1.0, 1.0, 1.0))));

//    for(float i=5; i<26; i+=1){
//        world.addShape(
//                new Triangle(
//                        Vector3(-24, -i, -15),
//                        Vector3(-24, -i, -63),
//                        Vector3(24, -i, -15),
//                        new DynMat(0.01, 0, Texture(), Vector3(20.0f / i, 20.0f / i, 20.0f / i))));
//    }
//world.addShape(new Triangle(Vector3(-24, -16, -15), Vector3(-24, -16, -63), Vector3(24, -16, -15), new DynMat(0, 0, Texture(1, 1, 1), Vector3(1, 1, 1))));
//    world.addShape(new Triangle(Vector3(-24, -24, -15), Vector3(-24, -24, -63), Vector3(24, -24, -15), new DynMat(0, 0, Texture(1, 1, 1), Vector3(0, 1, 1))));

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