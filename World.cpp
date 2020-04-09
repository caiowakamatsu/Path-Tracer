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

Vector3 World::colour(Ray ray) {
    HitRecord best = HitRecord(nullptr, ray);
    for(auto shape : shapes){
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }
    if (best.hit) {
        Vector3 intersectionPoint = ray.getPoint(best.distance);
        Vector3 currentColour = best.shape->colour(intersectionPoint, ray);
//        Ray reflective = best.shape->getReflectionRay(best);
        Vector3 recursive = colour(ray);
//      return recursive * 0.5f;
        return currentColour;
    } else return Vector3(204.0f, 255.0f, 255.0f);
}

Vector3 World::trace(Ray& ray) {
    return this->colour(ray);
}
