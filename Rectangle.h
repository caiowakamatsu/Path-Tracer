//
// Created by legend on 4/20/20.
//

#pragma once

#include "Shape.h"
#include "Triangle.h"

class Rectangle : public Shape {
private:
    Material* material;
    Triangle t0, t1;
    Vector3 normal;
    //Vector3 vertex0, vertex1, vertex2, vertex3, normal;
public:
    Rectangle(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Material* material);
    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Vector3 getUV(Vector3 &) override;
    Material* getMaterial() override;
};