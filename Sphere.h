//
// Created by legend on 3/20/20.
//
#pragma once

#include "Shape.h"
#include "Vector3.h"

class Sphere : public Shape {
public:
    Sphere(Vector3 *, float);
    Vector3 * origin;
    float radius;
    void intersect(Ray &, HitRecord &) override;
    Vector3 colour(Vector3 &, Ray &) override;
    ~Sphere();
private:
    float radius2;
};
