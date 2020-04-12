#pragma once

#include "vector"
#include "Shape.h"
#include "Vector3.h"
#include "Camera.h"
#include "ColourCache.h"
#include <vector>

class World {
private:
    int width, height, maxBounce, maxRefraction;
    float aspect;
    std::vector<Shape *> shapes;
    bool colour(Ray&, ColourCache&, std::vector<Ray>&);
public:
    World(int, int, int = 5, int = 5);
    ~World();
    void addShape(Shape *);
    void render(int*);
    Vector3 trace(Ray ray, int);
};
