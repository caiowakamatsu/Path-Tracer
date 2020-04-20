//
// Created by legend on 4/20/20.
//



#include <cmath>
#include "Triangle.h"
#include <Eigen/Dense>

typedef Eigen::Matrix3f mat3f;
typedef Eigen::Vector3f vec3f;

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material* m) {
    vertex0 = v0;
    vertex1 = v1;
    vertex2 = v2;
    material = m;
    normal = (vertex1 - vertex0).cross(vertex2 - vertex2);
}

void Triangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;
    rec.normal = normal;
    Vector3 v1v0 = vertex1 - vertex0;
    Vector3 v2v0 = vertex2 - vertex1;

    Vector3 pvec = ray.direction.cross(v2v0);
    float det = pvec.dot(v1v0);
    if(det != 0){
        float invDet = 1.0f / det;
        Vector3 tvec = ray.origin - vertex0;
        float u = tvec.dot(pvec) * invDet;
        if(!(u < 0 || u > 1)) {
            Vector3 qvec = tvec.cross(v1v0);
            float v = ray.direction.dot(qvec * invDet);
            if(!(v < 0 || u + v > 1)) {
                float t = v2v0.dot(qvec) * invDet;
                rec.hit = true;
                rec.distance = t;
            }
        }
    }

#ifdef og
    Vector3 v1v0 = vertex1 - vertex0;
    Vector3 v2v0 = vertex2 - vertex1;
    Vector3 r0v0 = ray.direction - vertex0;

    Vector3 n = v1v0.cross(v2v0);
    Vector3 q = r0v0.cross(ray.direction);
    float d = 1.0f / r0v0.dot(n);
    float u = d * -q.dot(v2v0);
    float v = d * q.dot(v1v0);
    float t = d * -n.dot(r0v0);
    if(!(u<0.0 || v<0.0 || (u+v)>1.0)){
        rec.distance = t;
        rec.hit = true;
    }
    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
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
#endif
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
