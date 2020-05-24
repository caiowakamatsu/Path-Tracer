//
// Created by legend on 4/18/20.
//
#pragma  once

#include "Material.h"

class DynMat : public Material {
private:
    float diffuse;
    float reflectiveness;
    Vector3 emission;
    Texture texture;
public:
    DynMat(float diffuse, float reflectiveness, Texture texture, Vector3 emission = Vector3());
    void transformRay(Ray& ray, HitRecord& record) override;
    void getColour(Vector3& outEmission, Vector3& outColour, Vector3& uv, float& reflectiveness, HitRecord& rec) override;
};