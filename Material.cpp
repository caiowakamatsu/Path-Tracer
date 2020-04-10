//
// Created by legend on 4/9/20.
//

#include "Material.h"

Material::Material(Vector3 c, float r) {
    colour = c;
    roughness = r;
}

void Material::getMaterialRay(Ray& ray) {

}