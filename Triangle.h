//
// Created by legend on 4/20/20.
//

#pragma once

#include <bvh/triangle.hpp>
#include "Vector3.h"
#include "Vertex.h"
#include "Material.h"

class Material;

class Triangle {
public:
    Vector3 normal, unnormalizedNormal;
    Vertex vertices[3];
    Material* material;
    bvh::Triangle<float> bvhTri;
    Triangle() = default;
    Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2, Material* Material);
    Vector3 getNormal(Vector3 &);
    Material* getMaterial();
    Vector3 getUv(Vector3 barycentric);
};
