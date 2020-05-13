//
// Created by legend on 4/29/20.
//

#include "AxisAlignedBB.h"

AxisAlignedBB::AxisAlignedBB(Vector3 origin, Vector3 size, Material* mat) : material(mat) {
    minb[0] = fmin(origin.x, origin.x + size.x);
    minb[1] = fmin(origin.y, origin.y + size.y);
    minb[2] = fmin(origin.z, origin.z + size.z);
    maxb[0] = fmax(origin.x, origin.x + size.x);
    maxb[1] = fmax(origin.y, origin.y + size.y);
    maxb[2] = fmax(origin.z, origin.z + size.z);
}

void AxisAlignedBB::intersect(Ray& ray, HitRecord& record) {
    float t1 = (minb[0] - ray.origin[0])*ray.inverse[0];
    float t2 = (maxb[0] - ray.origin[0])*ray.inverse[0];

    float tmin = fmin(t1, t2);
    float tmax = fmax(t1, t2);

    for (int i = 1; i < 3; ++i) {
        t1 = (minb[i] - ray.origin[i])*ray.inverse[i];
            t2 = (maxb[i] - ray.origin[i])*ray.inverse[i];

        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));
    }
}

Vector3 AxisAlignedBB::getNormal(Vector3& p) {
    return Vector3();
}

Vector3 AxisAlignedBB::getUV(Vector3 &) {
    return Vector3();
}

Material *AxisAlignedBB::getMaterial() {
    return material;
}