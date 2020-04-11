//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"

World::World(int w, int h, int m){
    width = w;
    height = h;
    maxBounce = m;
    aspect = (float) width / height;
}

World::~World() = default;

void World::addShape(Shape * shapePtr) {
    shapes.push_back(shapePtr);
}

// This returns a single ray trace
Vector3 World::colour(Ray ray) {
    /*
    {
        HitRecord best = HitRecord(nullptr, ray);
        for (auto shape : shapes) {
            HitRecord rec(shape, ray);
            shape->intersect(ray, rec);
            if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
        }
        if (best.hit) {
            Vector3 currentColour = best.shape->getMaterial().colour;
            if (depth < 5) {
                Vector3 normal = best.shape->getNormal(best.intersectionPoint);
                Ray recursiveRay = best.shape->getRecursiveRay(best);
                Vector3 recursive = colour(recursiveRay, depth);
                recursive.mix(currentColour, best.shape->getMaterial().absorb);
                return recursive;
            }
            // Todo: calculate light here
            return currentColour;
        }

    }*/
//    return Vector3(0.7, 0.7, 0.7);
    float t = 0.5f * (ray.direction.y + 1.0f);
    Vector3 max = Vector3(0.7, 0.7, 0.7) * (1 - t);
    Vector3 min = Vector3(0, 0, 0) * t;
    return max + min;
}

// This function returns the colour of a single path trace
Vector3 World::trace(Ray& ray) {
    for(int i=0; i<maxBounce; i++){

    }
    return this->colour(ray);
}

// Renders out the entire scene
void World::render(int* out) {
    auto camera = Camera(new Vector3(0, 5, 20), new Vector3(0, 0, -1), 30, aspect);
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            Ray ray = camera.getRay(
                    (float) x / width * 2 - 1,
                    (float) y / height * 2 - 1);
            Vector3 sample = trace(ray);

            out[x + y * width] =
                    ((int) ((sample.x) * 255)&0x0ff) << 16 |
                    ((int) ((sample.y) * 255)&0x0ff) << 8 |
                    (int) ((sample.z) * 255)&0x0ff;
        }
    }
}
