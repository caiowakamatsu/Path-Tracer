//
// Created by legend on 4/9/20.
//

#include "Material.h"
#include <cmath>

Material::Material(Vector3 c, float r, float a, bool re, float index, Texture* t) {
    colour = c;
    roughness = r;
    absorb = a;
    refract = re;
    ref_index = index;
    texture = t;
}
Material::~Material() {
    delete(texture);
}

void Material::transformRay(Ray& ray, std::vector<Ray>& rays, HitRecord& rec) {

    Ray copy = ray;

    Vector3 offset = rec.normal * 0.0001f;
    if(!refract){
        /* Handle the reflective ray, and diffuseness*/
        Vector3 rayOrigin = ray.direction;
        Vector3 a = rec.normal * rec.normal.dot(rec.ray.direction) * 2;
        Vector3 reflection = rayOrigin - a;
        ray.origin = rec.intersectionPoint + offset;
        ray.direction = reflection.toUnitVector();
        if(roughness > 0){
            Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
            point = point.toUnitVector();
            ray.direction.mix(point, roughness);
        }

    }
    /* Handles creating extra rays*/

    if(refract){
        // This ray is refraction
        Vector3 outNormal;
        float nit;
        Ray refracted = copy;
        if(ray.direction.dot(rec.normal) > 0){
            outNormal = rec.normal * -1;
            nit = ref_index;
        } else {
            outNormal = rec.normal;
            nit = 1.0f / ref_index;
        }
        Vector3 uv = ray.direction.toUnitVector();
        float dt = uv.dot(outNormal);
        float disc = 1.0f - nit*nit* (1 - dt * dt);
        if(disc > 0){
            ray.origin = rec.intersectionPoint + offset;
            Vector3 a = outNormal * dt;
            Vector3 b = uv - a;
            Vector3 c = outNormal*sqrtf(disc);
            ray.direction = b * nit - c;
        }
    }
}

void Material::getColour(float &outIntensity, Vector3 &outColour, Vector3 &uv) {
    if(texture != nullptr){
        // Get texture UV
        outColour = texture->getUV(uv.x, uv.y);

    } else outColour = this->colour;
    outIntensity = absorb;
}

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

