//
// Created by legend on 4/20/20.
//

#include "Rectangle.h"

Rectangle::Rectangle(Vertex v0, Vertex v1, Vertex v2, Vertex v3, Material* m) {
    t0 = Triangle(v0, v1, v3, m);
    t1 = Triangle(v2, v0, v3, m);
    material = m;
    normal = (v1.pos - v0.pos).cross(v2.pos - v0.pos).toUnitVector();
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

Material *Rectangle::getMaterial() {
    return material;
}
