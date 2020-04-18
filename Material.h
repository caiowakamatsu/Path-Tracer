//
// Created by legend on 4/9/20.
//
#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "HitRecord.h"
#include <vector>
#include "Texture.h"

class Material {
public:
    Vector3 colour;
    float roughness;
    float absorb;
    bool refract;
    float ref_index;
    Texture* texture;
    Material(Vector3, float, float, bool, float = 1, Texture* = nullptr);
    ~Material();
    void transformRay(Ray&, std::vector<Ray>&, HitRecord&);
    void getColour(float& outIntensity, Vector3& outColour, Vector3& uv);
private:
    bool canrefract(Vector3&, Vector3&, float, Vector3&);
};