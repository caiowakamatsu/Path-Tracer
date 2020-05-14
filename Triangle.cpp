//
// Created by legend on 4/20/20.
//
#include <cmath>
#include "Triangle.h"
#include <Eigen/Dense>
#include <iostream>

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Material* m) {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
    material = m;
}

void Triangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;

    Vector3 o = vertices[0].pos;
    Vector3 e0 = vertices[1].pos - o;
    Vector3 e1 = vertices[2].pos - o;
    Vector3 intersectionMat[3] = {ray.direction * -1, e0, e1};

    Vector3 c01 = intersectionMat[0].cross(intersectionMat[1]);
    Vector3 c12 = intersectionMat[1].cross(intersectionMat[2]);
    Vector3 c20 = intersectionMat[2].cross(intersectionMat[0]);

    float det = intersectionMat[0].dot(c12);
    float inverseDet = 1.0f / det;

    Vector3 inverseTransposedMat[3] = { c12*inverseDet, c20*inverseDet, c01*inverseDet };

    Vector3 dir = ray.origin - o;
    Vector3 tuv = Vector3(
            inverseTransposedMat[0].dot(dir),
            inverseTransposedMat[1].dot(dir),
            inverseTransposedMat[2].dot(dir));

    if(0 < tuv.x && 0.0f < tuv.y && 0.0f < tuv.z && tuv.y + tuv.z < 1.0f){
        rec.intersectionPoint = ray.getPoint(tuv.x);
        rec.distance = tuv.x;
        rec.u = tuv.y * vertices[1].u + tuv.z * vertices[2].u + (1.0f - tuv.y - tuv.z) * vertices[0].u;
        rec.v = tuv.y * vertices[1].v + tuv.z * vertices[2].v + (1.0f - tuv.y - tuv.z) * vertices[0].v;
        rec.normal = e0.cross(e1).toUnitVector();
        rec.hit = true;
    }
}

Vector3 Triangle::getNormal(Vector3 &) {
    return normal;
}

Material *Triangle::getMaterial() {
    return material;
}

AABB Triangle::getBoundingBox() {
    Vector3 a = vertices[0].pos;
    Vector3 b = vertices[1].pos;
    Vector3 c = vertices[2].pos;
    float minX = fmin(a.x, fmin(b.x, c.x));
    float minY = fmin(a.y, fmin(b.y, c.y));
    float minZ = fmin(a.z, fmin(b.z, c.z));
    float maxX = fmax(a.x, fmax(b.x, c.x));
    float maxY = fmax(a.y, fmax(b.y, c.y));
    float maxZ = fmax(a.z, fmax(b.z, c.z));
    return AABB(minX, minY, minZ, maxX, maxY, maxZ);
}
