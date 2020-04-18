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
    virtual void transformRay(Ray&, std::vector<Ray>&, HitRecord&) = 0;
    virtual void getColour(float& outIntensity, Vector3& outColour, Vector3& uv) = 0;
};