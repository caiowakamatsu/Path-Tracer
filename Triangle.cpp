//
// Created by legend on 4/20/20.
//
#include <cmath>
#include "Triangle.h"
#include <Eigen/Dense>
#include <iostream>

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material* m) {
    vertex0 = v0;
    vertex1 = v1;
    vertex2 = v2;
    material = m;
}

void Triangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;
    Vector3 e_1 = vertex1 - vertex0;
    Vector3 e_2 = vertex2 - vertex0;

    Vector3 n = e_1.cross(e_2).toUnitVector();

    Vector3 q = ray.direction.cross(e_2);
    float a = e_1.dot(q);

    if(n.dot(ray.direction) >= 0 || abs(a) <= 0.00001f){

    } else {
        Vector3 s = (ray.origin - vertex0) / a;
        Vector3 r = s.cross(e_1);

        float v0b = s.dot(q);
        float v1b = r.dot(ray.direction);
        float v2b = 1.0f - v0b - v1b;
        if(!(v0b < 0.0f || v1b < 0.0f || v2b < 0.0f)){
            rec.hit = true;
            rec.distance = e_2.dot(r);
            rec.intersectionPoint = ray.getPoint(rec.distance);
            rec.normal = n;
        }
    }

}

Vector3 Triangle::getNormal(Vector3 &) {
    return normal;
}

Vector3 Triangle::getUV(Vector3& point) {
    return Vector3(0, 0, 0);
}

Material *Triangle::getMaterial() {
    return material;
}
