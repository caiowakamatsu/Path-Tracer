//
// Created by legend on 3/20/20.
//

#pragma once

#include "vector3.h"

class ray {
public:
    vector3 origin, direction;
    ray(vector3, vector3);
    inline vector3 getPoint(float);
};
