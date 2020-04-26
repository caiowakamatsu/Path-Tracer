//
// Created by legend on 4/26/20.
//
#pragma once

#include "Material.h"

class NormalMat : public Material {
private:
    bool light;
public:
    NormalMat(bool light);
    void transformRay(Ray& ray, HitRecord& record) override;
    void getColour(Vector3& outEmission, Vector3& outColour, Vector3& uv, float& reflectiveness, HitRecord& rec) override;
};