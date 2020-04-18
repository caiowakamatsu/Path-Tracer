#pragma once

#include "vector"
#include "Shape.h"
#include "Vector3.h"
#include "Camera.h"
#include "ColourCache.h"
#include <vector>
#include "Texture.h"

class World {
private:
    int width, height, maxBounce, maxRefraction;
    float aspect;
    Texture& texture;
    std::vector<Shape *> shapes;
    bool colour(Ray& ray, HitRecord& out);
public:
    World(int, int, Texture&, int = 5, int = 5);
    ~World();
    void addShape(Shape *);
    void render(int*);
    Vector3 trace(Ray ray, int);
};
