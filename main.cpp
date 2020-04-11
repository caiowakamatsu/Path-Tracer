#include <iostream>
#include <chrono>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include <GL/glut.h>

constexpr int WIDTH = 800, HEIGHT = 800;
constexpr int ANTI_ALIASING_LEVEL = 2;
constexpr int AA_DIV = ANTI_ALIASING_LEVEL * ANTI_ALIASING_LEVEL;
constexpr float ANTI_ALIASING_OFFSET = 1.0f / (ANTI_ALIASING_LEVEL * 2);
constexpr float ASPECT = (float) WIDTH / (float) HEIGHT;

int* pixels;

void display(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_BYTE, pixels);
    glFlush();
}


int main(int argc, char **argv) {

    pixels = new int[WIDTH * HEIGHT]{0};
    auto world = World(WIDTH, HEIGHT, 4);
    world.addShape(new Sphere(Vector3(0, 7, -1), 5, Material(Vector3(1, 1, 1), 0, 0, false)));
    world.addShape(new Sphere(Vector3(0, -1000.5f, -1), 1000.0f, Material(Vector3(0.7, 0.7, 0.7), 0.01, 0, false)));

    auto start = std::chrono::high_resolution_clock::now();
    world.render(pixels);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    printf("Total Execution Time %.2fms\n",
            std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / 1000000.0f);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1000, 200);
    glutCreateWindow("Ray Tracer");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}