#pragma once

#include "vector"
#include "Shape.h"
#include "Vector3.h"
#include "Camera.h"

class World {
private:
    int width, height, maxBounce;
    float aspect;
    std::vector<Shape *> shapes;
    Vector3 colour(Ray);
public:
    World(int, int, int);
    ~World();
    void addShape(Shape *);
    void render(int*);
    Vector3 trace(Ray&);
};
