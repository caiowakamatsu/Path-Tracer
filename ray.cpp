//
// Created by legend on 3/20/20.
//

#include "ray.h"

ray::ray(vector3 origin, vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

vector3 ray::getPoint(float t) {
    return vector3(direction * t + origin);
}