//
// Created by legend on 4/29/20.
//

#pragma once

#include "Vector3.h"
#include "Shape.h"
#include <cmath>

class AxisAlignedBB : public Shape {
public:
    float a, b, c, d, e, f;
    Vector3 minb, maxb;
    Material* material;
    AxisAlignedBB(Vector3 origin, Vector3 size, Material* material);
    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Vector3 getUV(Vector3 &) override;
    Material* getMaterial() override;
};


