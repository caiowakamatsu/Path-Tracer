//
// Created by legend on 3/20/20.
//

#pragma once

#include "Vector3.h"

class Ray {
public:
    Ray(Vector3 &, Vector3 &);
    Vector3 origin, direction;
    Vector3 getPoint(float);
};
