//
// Created by legend on 3/20/20.
//

#include "Sphere.h"
#include "Vector3.h"
#include <cmath>
#include <iostream>

Sphere::Sphere(Vector3 origin, float radius, Material m) : mat(m) {
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
//    float a = ray.direction.dot(ray.direction);
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
        }
    }
}

Ray Sphere::getRecursiveRay(HitRecord& rec) {
    Vector3 normal = getNormal(rec.intersectionPoint);
    Vector3 rayOrigin = rec.ray.direction;
    Vector3 a = normal * normal.dot(rec.ray.direction) * 2;
    Vector3 reflection = rayOrigin - a;
    normal = normal * 0.0001f;
    Ray ret(rec.intersectionPoint + normal, reflection.toUnitVector());
    mat.getMaterialRay(ret);
    return ret;
}

Material& Sphere::getMaterial() {
    return mat;
}

Vector3 Sphere::getNormal(Vector3& point){
    return (point - this->origin).toUnitVector();
}