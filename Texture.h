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
    float xd = 0, yd = 0;
    bool textured = false;
    Vector3 colour = Vector3(), colourA = Vector3(), colourB = Vector3();
public:
    enum TextureType {CHECKERBOARD, IMAGE, SOLID};
    Texture::TextureType type;
    Texture();
    Texture(TextureType type, Vector3 colourA, Vector3 colourB, float xd = 0, float yd = 0);
    Texture(float r, float g, float b);
    explicit Texture(const char* path, float xd = 0, float yd = 0);
    Vector3 getUV(float u, float v);
    ~Texture();
};