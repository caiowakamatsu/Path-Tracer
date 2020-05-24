//
// Created by legend on 4/26/20.
//

#include "NormalMat.h"

NormalMat::NormalMat(bool l) {
    light = l;
}

void NormalMat::transformRay(Ray &ray, HitRecord &rec) {
    ray.origin = rec.intersectionPoint;
    Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
    point = point.toUnitVector();
    ray.direction = point;
}

void NormalMat::getColour(Vector3& outEmission, Vector3 &outColour, Vector3 &uv, float& reflectiveness, HitRecord& rec) {
//    Vector3 normalRGB = (rec.normal + 1) * 0.5f;
    Vector3 normalRGB = rec.normal * 0.5f + 0.5f;
    outEmission = light ? normalRGB : Vector3();
    outColour = !light ? normalRGB : Vector3();
    reflectiveness = 0;
}