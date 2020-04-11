//
// Created by legend on 4/9/20.
//
#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "HitRecord.h"

class Material {
public:
    Vector3 colour;
    float roughness;
    float absorb;
    bool refract;
    float ref_index;
    Material(Vector3, float, float, bool, float = 1);
    void getRefractiveRay(Ray&, Vector3&, HitRecord&);
    void getMaterialRay(Ray&);
private:
    bool canrefract(Vector3&, Vector3&, float, Vector3&);
};