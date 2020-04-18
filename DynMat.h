//
// Created by legend on 4/18/20.
//
#pragma  once

#include "Material.h"

class DynMat : public Material {
private:
    float diffuse;
    float reflectiveness;
    Texture texture;
public:
    DynMat(float diffuse, float reflectiveness, Texture texture);
    void transformRay(Ray& primaryRay, std::vector<Ray>& extraRays, HitRecord& record) override;
    void getColour(float& outIntensity, Vector3& outColour, Vector3& uv) override;
};