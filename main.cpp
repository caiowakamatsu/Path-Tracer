#include <iostream>
#include "File.h"
#include "World.h"
#include "Vector3.h"
#include "Ray.h"

constexpr int WIDTH = 255, HEIGHT = 255;

int main() {
    // Create the file object that lets us output intrgb arrays.
    File file("../renders", WIDTH, HEIGHT);
    int * pixels = new int[WIDTH * HEIGHT]{0};

    // Generate the world :p
    auto * world = new World();
    auto origin = Vector3(0, 0, 10);

    for(int x=0; x<WIDTH; x++)
        for(int y=0; y<HEIGHT; y++){
            auto dir = Vector3(0, 0, 0);
            auto ray = new Ray(origin, dir);
            auto sample = world->trace(ray);
            pixels[x + y * WIDTH] =
                    (int) (sample.x * 255) << 16 |
                    (int) (sample.y * 255) << 8 |
                    (int) (sample.z * 255);
        }

    file.setData(pixels);
    file.write();

    delete[](pixels);
    delete(world);

    return 0;
}