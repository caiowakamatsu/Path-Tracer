//
// Created by legend on 4/20/20.
//

#include "Rectangle.h"

Rectangle::Rectangle(Vector3 v0, Vector3 v1, Vector3 v2, Material* m) {
    vertex0 = v0;
    vertex1 = v1;
    vertex2 = v2;
    material = m;
    normal = (vertex1 - vertex0).cross(vertex2 - vertex0).toUnitVector();
}

void Rectangle::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;
    rec.normal = normal;
    Vector3 v1v0 = vertex1 - vertex0;
    Vector3 v2v0 = vertex2 - vertex0;

    Vector3 pvec = ray.direction.cross(v2v0);
    float det = pvec.dot(v1v0);
    if(det != 0){
        float invDet = 1.0f / det;
        Vector3 tvec = ray.origin - vertex0;
        float u = tvec.dot(pvec) * invDet;
        if(!(u < 0 || u > 1)) {
            Vector3 qvec = tvec.cross(v1v0);
            float v = ray.direction.dot(qvec * invDet);
            if(!(v < 0 || u + v > 2 || v > 1 || u > 1)) {
                float t = v2v0.dot(qvec) * invDet;
                rec.hit = true;
                rec.distance = t;
            }
        }
    }
}

Vector3 Rectangle::getNormal(Vector3& p) {
    return Vector3(normal);
}

Vector3 Rectangle::getUV(Vector3 &) {
    return Vector3();
}

Material *Rectangle::getMaterial() {
    return material;
}
