//
// Created by legend on 4/20/20.
//

#include "Rectangle.h"

Rectangle::Rectangle(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Material* m) {
    t0 = Triangle(v0, v1, v3, m);
    t1 = Triangle(v2, v0, v3, m);
    material = m;
    normal = (v1 - v0).cross(v2 - v0).toUnitVector();
}

void Rectangle::intersect(Ray& ray, HitRecord& rec) {
    HitRecord current = HitRecord(this, ray);
    t0.intersect(ray, current);
    t1.intersect(ray, rec);
    rec = rec.hit && current.hit ? (rec.hit < current.hit ? rec : current) : rec.hit && !current.hit ? rec : current;
}

Vector3 Rectangle::getNormal(Vector3& p) {
    return normal;
}

Vector3 Rectangle::getUV(Vector3 &) {
    return Vector3();
}

Material *Rectangle::getMaterial() {
    return material;
}
