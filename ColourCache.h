//
// Created by legend on 4/11/20.
//
#pragma once

#include "Vector3.h"

class ColourCache {
public:
    Vector3 colour{};
    int intensity{};
    bool a = false; // For null termination in trace function
    ColourCache() = default;
    ColourCache(Vector3 c, int i){
        colour = c;
        intensity = i;
    }
};