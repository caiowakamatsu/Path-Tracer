//
// Created by legend on 4/14/20.
//

#pragma once

#include "Vector3.h"
#include "stb_image.h"

class Texture {
private:
    int width{}, height{}, channels{};
    int* data = nullptr;
    float xd, yd;
    bool textured = false;
    Vector3 colour;
public:
    Texture() = default;
    Texture(float r, float g, float b);
    Texture(const char* path, float xd = 0, float yd = 0);
    Vector3 getUV(float u, float v);
    ~Texture();
};