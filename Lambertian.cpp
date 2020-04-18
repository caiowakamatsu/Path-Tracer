//
// Created by legend on 4/19/20.
//

#include "Lambertian.h"

#include <cmath>

Lambertian::Lambertian(Texture t, Vector3 e) : texture(t), emission(e) {

}

// Yo highkey dont use this idk whats wrong
void Lambertian::transformRay(Ray &ray, HitRecord &rec) {
    Vector3 offset = rec.normal * 0.0001f;
    ray.origin = rec.intersectionPoint + offset;
    Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
    point = point.toUnitVector();
    ray.direction = point;
}

void Lambertian::getColour(Vector3& outEmission, Vector3 &outColour, Vector3 &uv, float& reflectiveness, HitRecord& rec) {
    outEmission = emission;
    outColour = texture.getUV(uv.x, uv.y);
    reflectiveness = fmaxf(0, rec.normal.dot(rec.outRay.direction));
}
