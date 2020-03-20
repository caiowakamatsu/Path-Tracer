#pragma once

#include "vector"
#include "Shape.h"
#include "Vector3.h"

class World {
private:
    std::vector<Shape *> shapes;
public:
    World();
    ~World();
    void addShape(Shape *);
    Vector3 trace(Ray * ray);
};
