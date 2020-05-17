//
// Created by legend on 5/14/20.
//

#pragma once

#include "Shape.h"
#include "Ray.h"

#include <cmath>

class AABB {
public:
    Vector3 min, max;
    AABB() = default;
    AABB(Vector3 corner_a, Vector3 corner_b, bool safe = false);
    AABB(float a, float b, float c, float d, float e, float f, bool safe = false);

    bool intersect(Ray &ray);
    bool intersect(AABB &aabb);
    bool intersect(Vector3 &vector3);
    float getAreaRating();
    Vector3 getCenter();
    void extend(AABB& aabb);
};