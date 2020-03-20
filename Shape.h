//
// Created by legend on 3/20/20.
//

#pragma once

#include "Ray.h"

class Shape {
public:
    virtual float intersect(Ray &ray) = 0;
    virtual ~Shape() = 0;
};
