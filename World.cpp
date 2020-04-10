//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"

World::World() = default;
World::~World() = default;

void World::addShape(Shape * shapePtr) {
    shapes.push_back(shapePtr);
}

Vector3 World::colour(Ray ray, int depth) {
    depth++;
    HitRecord best = HitRecord(nullptr, ray);
    for(auto shape : shapes){
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }
    if (best.hit) {
        Vector3 currentColour = best.shape->getMaterial().colour;
        if (depth < 5) {
            Ray recursiveRay = best.shape->getRecursiveRay(best);
            best.shape->getMaterial().getMaterialRay(recursiveRay);
            Vector3 recursive = colour(recursiveRay, depth);
            recursive.mix(currentColour, best.shape->getMaterial().absorb);
            return recursive;
        }
        // Todo: calculate light here
        return currentColour;
    }
    float t = 0.5f * (ray.direction.y + 1.0f);
    Vector3 max = Vector3(0, 1, 1) * (1 - t);
    Vector3 min = Vector3(0, 0, 1) * t;
    return max + min;
}

Vector3 World::trace(Ray& ray) {
    int depth = 0;
    return this->colour(ray, depth);
}
