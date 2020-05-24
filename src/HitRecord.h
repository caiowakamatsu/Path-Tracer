//
// Created by legend on 3/20/20.
//

#pragma once

#include "Triangle.h"
#include "Ray.h"
#include "Vector3.h"

class Triangle;

struct HitRecord {
public:
    HitRecord(Triangle* s, Ray r) : ray(r) {
        hit = false;
        distance = -1.0f;
        triangle = s;
    }
    bool hit;
    float distance;
    float reflectiveness;
    float u, v;
    Ray ray;
    Ray outRay;
    Vector3 emission;
    Vector3 albedo;
    Triangle* triangle;
    Vector3 intersectionPoint;
    Vector3 normal;
};
