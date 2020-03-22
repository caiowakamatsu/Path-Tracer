//
// Created by legend on 3/20/20.
//

#pragma once

#include "Shape.h"
#include "Ray.h"
#include "Vector3.h"

class Shape;

struct HitRecord {
public:
    HitRecord(Shape *s, Ray * r) {
        hit = false;
        distance = -1.0f;
        shape = s;
        ray = r;
    }
    bool hit;
    float distance;
    Ray * ray;
    Shape * shape;
};
