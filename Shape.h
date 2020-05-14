//
// Created by legend on 3/20/20.
//

#pragma once

#include "Ray.h"
#include "HitRecord.h"
#include "Material.h"
#include "Vertex.h"

struct Material;
struct HitRecord;

class Shape {
public:
    virtual Material* getMaterial() = 0;
    virtual Vector3 getNormal(Vector3 &) = 0;
    virtual void intersect(Ray &, HitRecord&) = 0;
};
