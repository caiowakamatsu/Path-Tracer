//
// Created by legend on 3/18/20.
//

#include "World.h"

World::World() {
}

World::~World(){
    for(auto ptr : shapes){
        delete(ptr);
    }
}

void World::addShape(Shape * shapePtr) {
    shapes.push_back(shapePtr);
}

Vector3 World::colour(Ray ray) {
    HitRecord best(nullptr, &ray);
    for(auto shape : shapes){
        HitRecord rec(shape, &ray);
        shape->intersect(ray, rec);
        if((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }
    Vector3 intersectionPoint;
    if(best.hit) intersectionPoint = best.ray->getPoint(best.distance);
    return best.hit ? best.shape->colour(intersectionPoint, *best.ray) : Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 World::trace(Ray ray) {
    return this->colour(ray);
}
