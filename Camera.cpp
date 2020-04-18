//
// Created by legend on 3/22/20.
//

#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(Vector3 * origin, Vector3 * direction, float fov, float aspect) {
    float theta = fov * 3.1415f / 180;
    float half_height = tanf(theta / 2);
    float half_width = aspect * half_height;
    (*direction) = (*direction).toUnitVector();
    this->origin = *origin;
    Vector3 u = Vector3(0, 1, 0).cross(*direction);
    Vector3 v = u.cross(*direction);
    center = this->origin + *direction;
    horizontal = u * 2 * half_width;
    vertical = v * 2 * half_height;
    delete(direction);
}

Ray Camera::getRay(float x, float y) {
    auto xOffset = horizontal * x;
    auto yOffset = vertical * y;
    Vector3 e = (center + xOffset + yOffset - origin).toUnitVector();
//Vector3 e = Vector3(0, 0, 0);
    return Ray(origin, e);
}
