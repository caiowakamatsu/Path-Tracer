//
// Created by legend on 4/20/20.
//

#pragma once

#include "Shape.h"

class Triangle : public Shape {
public:
    Vector3 vertex0, vertex1, vertex2, normal;
    Material* material;
    Triangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, Material* Material);
    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Vector3 getUV(Vector3 &) override;
    Material* getMaterial() override;
};
