#pragma once

#include "vector"
#include "Shape.h"
#include "Vector3.h"
#include "Camera.h"

class World {
private:
    std::vector<Shape *> shapes;
    Vector3 colour(Ray ray);
public:
    World();
    ~World();
    void addShape(Shape *);
    Vector3 trace(Ray ray);
};
