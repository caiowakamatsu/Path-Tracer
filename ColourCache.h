//
// Created by legend on 4/11/20.
//
#pragma once

#include "Vector3.h"

class ColourCache {
public:
    Vector3 colour{};
    float intensity{};
    ColourCache() = default;
    ColourCache(Vector3 c, float i){
        colour = c;
        intensity = i;
    }
};