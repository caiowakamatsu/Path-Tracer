//
// Created by legend on 3/20/20.
//
#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "Material.h"

class Sphere : public Shape {
public:
    Sphere(Vector3, float, Material);
    Vector3 origin;
    float radius;
    Material mat;
    void intersect(Ray &, HitRecord &) override;
    Ray getRecursiveRay(HitRecord&) override;
    Vector3 getNormal(Vector3 &) override;
    Material& getMaterial() override;
    ~Sphere();
private:
    float radius2;
};
