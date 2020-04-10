#include <iostream>
#include <chrono>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"

constexpr int WIDTH = 800, HEIGHT = 800;
constexpr int ANTI_ALIASING_LEVEL = 2;
constexpr int AA_DIV = ANTI_ALIASING_LEVEL * ANTI_ALIASING_LEVEL;
constexpr float ANTI_ALIASING_OFFSET = 1.0f / (ANTI_ALIASING_LEVEL * 2);
constexpr float ASPECT = (float) WIDTH / (float) HEIGHT;

int main() {
    // Create the file object that lets us output intrgb arrays.
    auto file = new File("../renders", WIDTH, HEIGHT);
    auto pixels = new int[WIDTH * HEIGHT]{0};

    // Make the camera
    auto camera = new Camera(new Vector3(0, 5, 20), new Vector3(0, 0, -1), 30, ASPECT);

    // Generate the world :p
    auto world = new World();
    world->addShape(new Sphere(Vector3(0, 5, -1), 5, Material(Vector3(1, 1, 1), 10)));
    world->addShape(new Sphere(Vector3(0, -1000.5f, -1), 1000.0f, Material(Vector3(1, 1, 1), 10)));

    auto start = std::chrono::high_resolution_clock::now();
    for(int x=0; x<WIDTH; x++)
        for(int y=0; y<HEIGHT; y++){
            Vector3 sample = Vector3();
            for(int a=1; a<=ANTI_ALIASING_LEVEL; a++){
                for(int b=1; b<=ANTI_ALIASING_LEVEL; b++) {
                    Ray ray = camera->getRay(
                            (float) (x + a * ANTI_ALIASING_OFFSET) / WIDTH * 2 - 1,
                            (float) (y + b * ANTI_ALIASING_OFFSET) / HEIGHT * 2 - 1);
                    auto aa_sample = world->trace(ray);
                    sample += aa_sample;
                }
            }

            pixels[x + y * WIDTH] =
                    ((int) ((sample.x / AA_DIV) * 255)&0x0ff) << 16 |
                    ((int) ((sample.y / AA_DIV) * 255)&0x0ff) << 8 |
                    (int) ((sample.z / AA_DIV) * 255)&0x0ff;
        }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    printf("Total Execution Time %.2fms\n", std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / 1000000.0f);
    file->setData(pixels);
    file->write();
    file->open();

    delete(file);
    delete(world);
    delete(camera);

    return 0;
}