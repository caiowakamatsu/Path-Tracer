//
// Created by legend on 4/9/20.
//
#pragma once

#include "Vector3.h"
#include "Ray.h"

class Material {
public:
    Vector3 colour;
    float roughness;
    float absorb;
    Material(Vector3, float, float);
    void getMaterialRay(Ray&);
};