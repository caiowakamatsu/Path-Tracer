//
// Created by legend on 4/19/20.
//

#include "Lambertian.h"

#include <cmath>

Lambertian::Lambertian(Texture t, Vector3 e) : texture(t), emission(e) {

}

// Yo highkey dont use this idk whats wrong
// Hey past me, I should have fixed this. If this turns out to not be correct again im going to cry
void Lambertian::transformRay(Ray &ray, HitRecord &rec) {
    Vector3 offset = rec.normal * 0.001f;
    ray.origin = rec.intersectionPoint + offset;
    float x = drand48();
    float y = drand48();
    float phi =  2.0f * M_PI * x;
    float cosTheta = 2.0f * y - 1.0f;
    float a = sqrtf(1.0f - cosTheta * cosTheta);
    ray.direction = (rec.normal + Vector3(a * cosf(phi), a * sinf(phi), cosTheta)).toUnitVector();
}

void Lambertian::getColour(Vector3& outEmission, Vector3 &outColour, Vector3 &uv, float& reflectiveness, HitRecord& rec) {
    outEmission = emission;
    outColour = texture.getUV(uv.x, uv.y);
    reflectiveness = fmaxf(0, rec.normal.dot(rec.outRay.direction));
}
