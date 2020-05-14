//
// Created by legend on 3/20/20.
//

#include "Sphere.h"
#include "Vector3.h"
#include <cmath>

Sphere::Sphere(Vector3 origin, float radius, Material* m) : mat(m) {
    this->origin = origin;
    this->radius = radius;
    this->radius2 = radius * radius;
}

Sphere::~Sphere() {
    //delete(this->origin);
}

void Sphere::intersect(Ray & ray, HitRecord & record) {
    record.shape = this;
    Vector3 oc = ray.origin - this->origin;
    float b = ray.direction.dot(oc);
    float c = oc.dot(oc) - this->radius2;
    float delta = b * b - c;
    record.hit = delta > 0.0f;
    if(record.hit){
        delta = sqrtf(delta);
        float t0 = (-b-delta);
        float t1 = (-b+delta);
        if(t0 < 0 || t1 < 0) record.hit = false; else {
            record.distance = t0 < t1 ? t0 : t1;
            record.intersectionPoint = ray.getPoint(record.distance);
            record.normal = getNormal(record.intersectionPoint);
            record.u = 0.5f + atan2f(record.normal.z, record.normal.x) / (2 * M_PI);
            record.v = 0.5f - asinf(record.normal.y) / M_PI;
        }
    }
}

Material* Sphere::getMaterial() {
    return mat;
}

Vector3 Sphere::getNormal(Vector3& point){
    return (point - this->origin).toUnitVector();
}

AABB Sphere::getBoundingBox() {
    float minX = origin.x - radius;
    float minY = origin.y - radius;
    float minZ = origin.z - radius;
    float maxX = origin.x + radius;
    float maxY = origin.y + radius;
    float maxZ = origin.z + radius;
    return AABB(minX, minY, minZ, maxX, maxY, maxZ);
}
