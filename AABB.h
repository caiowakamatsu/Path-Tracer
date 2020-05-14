//
// Created by legend on 5/14/20.
//

#pragma once

#include "Shape.h"
#include "Ray.h"

#include <cmath>

class AABB {
private:
    Vector3 min, max;
public:
    AABB() = default;
    AABB(Vector3 corner_a, Vector3 corner_b, bool safe = false);
    AABB(float a, float b, float c, float d, float e, float f, bool safe = false);

    bool intersect(Ray &ray);
};