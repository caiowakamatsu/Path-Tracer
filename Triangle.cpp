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
    normal = (v1.pos - v0.pos).cross(v2.pos - v0.pos).toUnitVector();
    material = m;
}

Vector3 Triangle::getNormal(Vector3 &) {
    return normal;
}

Material *Triangle::getMaterial() {
    return material;
}

Vector3 Triangle::getUv(Vector3 barycentric) {
    return Vector3(
            barycentric.y * vertices[1].u + barycentric.z * vertices[2].u +
            (1.0f - barycentric.y - barycentric.z) * vertices[0].u,
            barycentric.y * vertices[1].v + barycentric.z * vertices[2].v +
            (1.0f - barycentric.y - barycentric.z) * vertices[0].v, 0);
}
