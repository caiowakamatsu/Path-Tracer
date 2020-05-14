//
// Created by legend on 5/14/20.
//

#pragma once

#include "Vector3.h"

class Vertex {
public:
    Vector3 pos;
    float u, v;
    Vertex() = default;
    Vertex(Vector3 position, float u, float v);
};


