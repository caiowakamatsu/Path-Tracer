//
// Created by legend on 4/20/20.
//

#pragma once

#include "Shape.h"

class Rectangle : public Shape {
public:

    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Vector3 getUV(Vector3 &) override;
    Material* getMaterial() override;
};