//
// Created by legend on 3/20/20.
//
#pragma once

#include "Shape.h"
#include "Vector3.h"

class Sphere : Shape {
public:
    Sphere(Vector3 *, float);
    Vector3 origin;
    float radius;
};
