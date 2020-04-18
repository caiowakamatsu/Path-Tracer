//
// Created by legend on 4/19/20.
//

#include "Glass.h"
#include <cmath>
Glass::Glass(float r) : refIndex(r) {

}

void Glass::transformRay(Ray &ray, HitRecord &record) {
    Vector3 outwardNormal;
    Vector3 reflected = ray.direction.reflect(record.normal);
    float nit;
    float cosine;
    if(ray.direction.dot(record.normal) > 0){
        outwardNormal = record.normal * -1.0f;
        nit = refIndex;
        cosine = refIndex * ray.direction.dot(record.normal) / ray.direction.length();
    } else {
        outwardNormal = record.normal;
        nit = 1.0f / refIndex;
        cosine = -ray.direction.dot(record.normal) / ray.direction.length();
    }
    Vector3 refracted;
    float reflectChance;
    if(refract(ray.direction, outwardNormal, nit, refracted)){
        reflectChance = schlick(cosine, refIndex);
    } else {
        ray = Ray(record.intersectionPoint, reflected);
        reflectChance = 1;
    }
    if(drand48() < reflectChance) {
        ray = Ray(record.intersectionPoint, reflected);
    } else {
        ray = Ray(record.intersectionPoint + outwardNormal * -0.1f, refracted);
    }
}

bool Glass::refract(Vector3 &v, Vector3 &n, float nit, Vector3 &refracted) {
    Vector3 uv = v.toUnitVector();
    float dt = uv.dot(n);
    float disc = 1.0f - nit * nit * (1 - dt * dt);
    if(disc > 0){
        refracted = (uv - n * dt) * nit - n * sqrtf(disc);
        return true;
    }
    return false;
}
void Glass::getColour(Vector3 &outEmission, Vector3 &outColour, Vector3 &uv, float &reflectiveness, HitRecord &rec) {
    outEmission = Vector3(0, 0, 0);
    outColour = Vector3(0, 0, 0);
    reflectiveness = 1;
}

float Glass::schlick(float cosine, float refIndex) {
    float r0 = (1.0f - refIndex) / (1.0f + refIndex);
    r0 = r0 * r0;
    return r0 + 1.0f - r0 * powf((1 - cosine), 5);
}
