//
// Created by legend on 4/19/20.
//

#include "Plane.h"

Plane::Plane(Vector3 l, Vector3 n, Material* m) : location(l), normal(n), material(m) {

}

void Plane::intersect(Ray& ray, HitRecord& rec) {
    rec.shape = this;
    float denom = normal.dot(ray.direction);
    if(denom > 0.00001f){
        float t = (location - ray.origin).dot(normal) / denom;
        if(t >= 0){
            rec.hit = true;
            rec.intersectionPoint = ray.getPoint(t);
            rec.normal = normal;
            rec.distance = t;
        } else {
            rec.hit = false;
        }
    } else {
        rec.hit = false;
    }
}

Vector3 Plane::getNormal(Vector3 &) {
    return normal;
}

Vector3 Plane::getUV(Vector3& point) {
    return Vector3();
}

Material *Plane::getMaterial() {
    return material;
}
