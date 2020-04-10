//
// Created by legend on 4/9/20.
//

#include "Material.h"
#include <cmath>

Material::Material(Vector3 c, float r, float a) {
    colour = c;
    roughness = r;
    absorb = a;
}

void Material::getMaterialRay(Ray& ray) {
    Vector3 point;
    do {
        point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
    } while (point.lengthSq() >= 1.0f);
    point = point.toUnitVector();
    ray.direction.mix(point, roughness);
}