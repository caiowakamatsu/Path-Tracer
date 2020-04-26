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
    unnormalizedNormal = (vertex1 - vertex0).cross(vertex2 - vertex0);
    normal = unnormalizedNormal.toUnitVector();
}

void Triangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;

    Vector3 v1v0 = vertex1 - vertex0;
    Vector3 v2v0 = vertex2 - vertex0;
    Vector3 r0v0 = ray.origin - vertex0;

    Vector3 n = v1v0.cross(v2v0);
    Vector3 q = r0v0.cross(ray.direction);
    float d = 1.0f / ray.direction.dot(n);
    float u = d * -q.dot(v2v0);
    float v = d * q.dot(v1v0);
    float t = d * -n.dot(r0v0);

    if(!(u<0.0 || v<0.0 || (u+v)>1.0)){
        rec.normal = normal;
        rec.hit = true;
        rec.distance = t;
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
