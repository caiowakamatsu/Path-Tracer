//
// Created by legend on 3/22/20.
//

#include "Camera.h"
#include <cmath>
#include <iostream>

#include <iostream>

Camera::Camera(Vector3 lookfrom, Vector3 lookat, float fov, float aspect) {
    float theta = fov * 3.1415f / 180;
    float half_height = tanf(theta / 2);
    float half_width = aspect * half_height;
    origin = lookfrom;
    Vector3 w = (lookat - lookfrom).toUnitVector();
    std::cout << w.x << ", " << w.y << ", " << w.z << std::endl;
    Vector3 u = Vector3(0, 1, 0).cross(w).toUnitVector();
    Vector3 v = w.cross(u);
    center = origin + w;
    horizontal = u * 2 * half_width;
    vertical = v * 2 * half_height;
}

Ray Camera::getRay(float x, float y) {
    auto xOffset = horizontal * x;
    auto yOffset = vertical * y;
    Vector3 e = ((center + xOffset + yOffset) - origin).toUnitVector();
    return Ray(origin, e);
}
