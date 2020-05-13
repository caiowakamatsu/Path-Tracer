//
// Created by legend on 3/20/20.
//

#pragma once

#include "Vector3.h"

class Ray {
public:
    Ray();
    Ray(Vector3, Vector3);
    Vector3 origin, direction, inverse;
    Vector3 getPoint(float);
};
