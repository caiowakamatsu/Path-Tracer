#include <iostream>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"

constexpr int WIDTH = 52, HEIGHT = 52;
constexpr float ASPECT = (float) WIDTH / (float) HEIGHT;

int main() {
    // Create the file object that lets us output intrgb arrays.
    File * file = new File("../renders", WIDTH, HEIGHT);
    int * pixels = new int[WIDTH * HEIGHT]{0};

    // Make the camera
    auto camera = new Camera(new Vector3(0, 0, 10), new Vector3(0, 0, -1), 90, ASPECT);

    // Generate the world :p
    World * world = new World();
    world->addShape(new Sphere(new Vector3(0, 0, -10), 15.0f));
//    world->addShape(new Sphere(new Vector3(0, -120.5f, -10), 100.0f));
    Vector3 origin = Vector3(0, 0, 10);

    for(int x=0; x<WIDTH; x++)
        for(int y=0; y<HEIGHT; y++){
            Ray * ray = camera->getRay((float) x / WIDTH * 2 - 1, (float) y / HEIGHT * 2 - 1);
            auto sample = world->trace(ray);

            int r = (int) (sample.x * 255);
            int g = (int) (sample.y * 255);
            int b = (int) (sample.z * 255);

            pixels[x + y * WIDTH] =((r&0x0ff) << 16 | (g&0x0ff) << 8 | b&0x0ff);
            delete(ray);
        }

    file->setData(pixels);
    file->write();

    delete(file);
    delete(world);

    return 0;
}