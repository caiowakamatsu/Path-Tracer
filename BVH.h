//
// Created by legend on 5/14/20.
//

#pragma once

#include "Shape.h"
#include "AABB.h"

#include <vector>
#include <limits>

class BVH { // Note: this is actually a BVH node, but I decided to call it BVH because it's shorter and more concise.
public:
    AABB self;
    BVH* children[2] {nullptr, nullptr};
    std::vector<Shape*> shapes;
    BVH() = default;
    BVH(AABB aabb);

    void split(int MaxPerNode);
    bool isEnd();
    void traverse(Ray& ray, HitRecord& record);
};


