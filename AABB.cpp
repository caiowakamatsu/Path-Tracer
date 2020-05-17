//
// Created by legend on 5/14/20.
//

#include "AABB.h"

AABB::AABB(Vector3 corner_a, Vector3 corner_b, bool safe) {
    if(safe){
        min = Vector3(
                fmin(corner_a.x, corner_b.x),
                fmin(corner_a.y, corner_b.y),
                fmin(corner_a.z, corner_b.z));
        max = Vector3(
                fmax(corner_a.x, corner_b.x),
                fmax(corner_a.y, corner_b.y),
                fmax(corner_a.z, corner_b.z));
    } else {
        min = corner_a;
        max = corner_b;
    }
}

AABB::AABB(float a, float b, float c, float d, float e, float f, bool safe) {
    if(safe){
        min = Vector3(
                fmin(a, d),
                fmin(b, e),
                fmin(c, f));
        max = Vector3(
                fmax(a, d),
                fmax(b, e),
                fmax(c, f));
    } else {
        min = Vector3(a, b, c);
        max = Vector3(d, e, f);
    }
}

bool AABB::intersect(Ray& ray){
    float t1 = (min[0] - ray.origin[0]) * ray.inverse[0];
    float t2 = (max[0] - ray.origin[0]) * ray.inverse[0];

    float tmin = fmin(t1, t2);
    float tmax = fmax(t1, t2);

    for(int i=1; i<3; i++){
        t1 = (min[i] - ray.origin[i]) * ray.inverse[i];
        t2 = (max[i] - ray.origin[i]) * ray.inverse[i];

        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));
    }
    return tmax > fmax(tmin, 0.0);
}


bool AABB::intersect(AABB &aabb) {
    for(int i=0; i<3; i++)
        if(aabb.min[i] > max[i] || aabb.max[i] < min[i]) return false;
    return true;
}

bool AABB::intersect(Vector3 &vector3) {
    for(int i=0; i<3; i++)
        if(!(min[i] < vector3[i] && vector3[i] < max[i])) return false;
    return true;
}

float AABB::getAreaRating() {
    float edge0 = max.x - min.x;
    float edge1 = max.y - min.y;
    float edge2 = max.z - min.z;
    float area = edge0 * edge1;
    area += edge1 * edge2;
    area += edge0 * edge2;
    return area;
}

Vector3 AABB::getCenter(){
    return Vector3(
            (min[0] + max[0]) * .5f,
            (min[1] + max[1]) * .5f,
            (min[2] + max[2]) * .5f);
}

void AABB::extend(AABB &aabb) {
    for(int i=0; i<3; i++) /* go through each axis */ {
        min[i] = fmin(aabb.min[i], min[i]);
        max[i] = fmax(aabb.max[i], max[i]);
    }
}