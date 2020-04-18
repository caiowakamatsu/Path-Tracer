//
// Created by legend on 4/19/20.
//

#pragma once

#include "Material.h"

class Glass : public Material {
private:
    float refIndex = 1;
    bool refract(Vector3& v, Vector3& n, float nit, Vector3& refracted);
    float schlick(float cosine, float refIndex);
public:
    Glass() = default;
    Glass(float refIndex);
    void transformRay(Ray& ray, HitRecord& record) override;
    void getColour(Vector3& outEmission, Vector3& outColour, Vector3& uv, float& reflectiveness, HitRecord& rec) override;
};
