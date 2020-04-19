//
// Created by legend on 4/20/20.
//

#include "Triangle.h"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material* m) {
    vertex0 = v0;
    vertex1 = v1;
    vertex2 = v2;
    material = m;
    normal = (vertex1 - vertex0).cross(vertex2 - vertex2);
}

void Triangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;
    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex1;
    h = ray.direction.cross(edge2);
    a = edge1.dot(edge2);
    if(a > -0.000001f && a < 0.000001f){
        rec.hit = false;
    } else {
        f = 1.0f / a;
        s = ray.origin - vertex0;
        u = f * s.dot(h);
        if(u < 0.0 || u > 1.0){
            rec.hit = false;
        } else {
            q = s.cross(edge1);
            v = f * ray.direction.dot(q);
            if(v < 0.0f || u + v > 1.0){
                rec.hit = false;
            } else {
                float t = f * edge2.dot(q);
                if(t > 0.000001f){
                    rec.distance = t;
                    rec.hit = true;
                    rec.normal = edge1.cross(edge2);
                }
            }
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
