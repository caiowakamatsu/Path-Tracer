//
// Created by legend on 4/19/20.
//

#pragma once

#include "Material.h"

class Lambertian : public Material {
private:
    Vector3 emission;
    Texture texture;
public:
    Lambertian(Texture texture, Vector3 emission = Vector3());
    void transformRay(Ray& ray, HitRecord& record) override;
    void getColour(Vector3& outEmission, Vector3& outColour, Vector3& uv, float& reflectiveness, HitRecord& rec) override;
};