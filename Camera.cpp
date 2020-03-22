//
// Created by legend on 3/22/20.
//

#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(Vector3 * origin, Vector3 * direction, float fov, float aspect) {
    float theta = fov * 3.1415f / 180;
    float half_width = tanf(theta / 2);
    float half_height = aspect * half_width;
    this->origin = origin;
    Vector3 u = Vector3(0, 1, 0).cross(*direction);
    Vector3 v = u.cross(*direction);
    center = new Vector3();
    (*this->origin + *direction).copyTo(center);
    horizontal = new Vector3();
    (u * 2 * half_width).copyTo(horizontal);
    vertical = new Vector3();
    (v * 2 * half_height).copyTo(vertical);
    delete(direction);
}

Ray * Camera::getRay(float x, float y) {
    auto xOffset = (*horizontal)* x;
    auto yOffset = (*vertical)* y;
    Vector3 e = true ?
            ((*center + xOffset + yOffset) - *origin).toUnitVector() :
                Vector3(x, y, -0.2f).toUnitVector();
    std::cout << "Screen Location X: " << e.x << ", Y: " << e.y << ", Z: " << e.z << std::endl;
    return new Ray(*origin, e);
}

Camera::~Camera() {
    delete(origin);
    delete(horizontal);
    delete(vertical);
    delete(center);
}
