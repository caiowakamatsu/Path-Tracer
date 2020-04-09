//
// Created by legend on 3/20/20.
//

#pragma once

#include "Ray.h"
#include "HitRecord.h"

class Shape {
public:
    virtual Vector3 colour(Vector3 &, Ray&) = 0;
    virtual Ray getReflectionRay(HitRecord& rec) = 0;
    virtual void intersect(Ray &, HitRecord&) = 0;
};
