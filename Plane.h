//
// Created by legend on 4/19/20.
//

#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "Material.h"

class Plane : public Shape {
public:
    Vector3 location, normal;
    Material* material;
    Plane(Vector3 location, Vector3 normal, Material* mat);

    void intersect(Ray &, HitRecord &) override;
    Vector3 getNormal(Vector3 &) override;
    Vector3 getUV(Vector3 &) override;
    Material* getMaterial() override;
};

