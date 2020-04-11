//
// Created by legend on 3/20/20.
//

#include "Ray.h"

Ray::Ray() = default;
Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Vector3 Ray::getPoint(float t) {
    return direction * t + origin;
}