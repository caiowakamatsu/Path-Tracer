//
// Created by legend on 3/22/20.
//
#pragma once

#include "Vector3.h"
#include "Ray.h"

class Camera {
private:
    Vector3 vertical, horizontal, center;
public:
    Vector3 origin;
    float fov;

    Camera(Vector3 lookfrom, Vector3 lookat, float, float);
    Ray getRay(float x, float y);
};