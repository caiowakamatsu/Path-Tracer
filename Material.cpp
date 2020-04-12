//
// Created by legend on 4/9/20.
//

#include "Material.h"
#include <cmath>

Material::Material(Vector3 c, float r, float a, bool re, float index) {
    colour = c;
    roughness = r;
    absorb = a;
    refract = re;
    ref_index = index;
}

void Material::transformRay(Ray& ray, std::vector<Ray>& rays, HitRecord& rec) {

    Ray copy = ray;

    /* Handle the reflective ray, and diffuseness*/
    Vector3 rayOrigin = ray.direction;
    Vector3 a = rec.normal * rec.normal.dot(rec.ray.direction) * 2;
    Vector3 reflection = rayOrigin - a;
    Vector3 offset = rec.normal * 0.0001f;
    ray.origin = rec.intersectionPoint + offset;
    ray.direction = reflection.toUnitVector();
    if(roughness > 0){
        Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
        point = point.toUnitVector();
        ray.direction.mix(point, roughness);
    }
    /* Handles creating extra rays*/

    if(refract){
        // This ray is refraction
        Vector3 outNormal;
        float nit;
        Ray refracted = copy;
        if(refracted.direction.dot(rec.normal) > 0){
            outNormal = rec.normal * -1;
            nit = ref_index;
        } else {
            outNormal = rec.normal;
            nit = 1.0f / ref_index;
        }
        Vector3 uv = copy.direction.toUnitVector();
        float dt = uv.dot(outNormal);
        float disc = 1.0f - nit*nit* (1 - dt * dt);
        if(disc > 0){
            refracted.origin = rec.intersectionPoint + offset;
            Vector3 a = outNormal * dt;
            Vector3 b = uv - a;
            Vector3 c = outNormal*sqrtf(disc);
            refracted.direction = b * nit - c;
            rays.push_back(refracted);
        }
    }
}

/*
void Material::getRefractiveRay(Ray& ray, Vector3& normal, HitRecord& rec){
    Vector3 rayDirection = ray.direction;
    Vector3 outNormal;
    float nit;
    float cosine;
    if(ray.direction.dot(normal) > 0){
        outNormal = normal * -1;
        nit = ref_index;
        cosine = ray.direction.dot(normal) /
                ray.direction.length() * ref_index;
    } else {
        outNormal = normal;
        nit = 1.0f / ref_index;
        cosine = -ray.direction.dot(normal) / ray.direction.length();
    }
    ray.direction.refract(outNormal, ref_index);
    Vector3 offset = outNormal * 0.0001f;
    ray.origin = rec.intersectionPoint + offset;
}*/

bool Material::canrefract(Vector3& v, Vector3& n, float nit, Vector3& ref) {
    Vector3 uv = v.toUnitVector();
    float dt = uv.dot(n);
    float disc = 1.0 - nit*nit*(1-dt*dt);
    if(disc > 0){
        Vector3 a = n * dt;
        a = uv - a;
        a = a * nit;
        a -= n;
        ref = a * sqrtf(disc);
        return true;
    }
    return false;
}
