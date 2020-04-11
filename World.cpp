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
bool World::colour(Ray& ray, ColourCache& cache) {
    HitRecord best(nullptr, ray);

    // Main intersection loop
    for(auto shape : shapes){
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }

    if(!best.hit){ // This runs if there was no intersection, and it hit the skyyyyyy
        // Todo: replace with skybox to make look hecka cool
        float t = 0.5f * (ray.direction.y + 1.0f);
        Vector3 max = Vector3(1, 1, 1) * (1 - t);
        Vector3 min = Vector3(0, 0, 1) * t;
        cache.colour = max + min;
        cache.intensity = 1;
        return false;
    } else { // Compute colour and intensity at intersection point and new ray
        ray = best.shape->getRecursiveRay(best);
        cache.colour = best.shape->getMaterial().colour;
        cache.intensity = 1;
        return true;
    }
}

// This function returns the colour of a single path trace
Vector3 World::trace(Ray ray) {
    int actualBounces = -1;
    ColourCache caches[maxBounce];
    for(int i=0; i<maxBounce; i++){
        actualBounces++;
        if(!colour(ray,caches[i])) break;
    }
    Vector3 finalColour = caches[actualBounces].colour;
    for(int i=actualBounces-1; i>=0; i--){
        finalColour.mix(caches[i].colour, 0.5f);
    }
    return finalColour;
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

            out[x + (height-y-1) * width] =
                    255 << 24 |
                    (((int) ((sample.z) * 255))&0x0ff) << 16 |
                    (((int) ((sample.y) * 255))&0x0ff) << 8 |
                    (((int) ((sample.x) * 255))&0x0ff) << 0;
        }
    }
}
