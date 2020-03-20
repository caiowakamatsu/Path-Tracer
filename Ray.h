//
// Created by legend on 3/20/20.
//

#pragma once

#include "Vector3.h"

class Ray {
public:
    Vector3 origin, direction;
    Ray(Vector3 &, Vector3 &);
    inline Vector3 getPoint(float);
};
