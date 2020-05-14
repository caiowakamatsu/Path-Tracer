//
// Created by legend on 4/20/20.
//

#pragma once

#include "Shape.h"

class Triangle : public Shape {
public:
    Vector3 normal, unnormalizedNormal;
    Vertex vertices[3];
    Material* material;
    Triangle() = default;
    Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2, Material* Material);
    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Material* getMaterial() override;
    AABB getBoundingBox() override;
};
