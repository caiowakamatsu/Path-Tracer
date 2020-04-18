//
// Created by legend on 4/14/20.
//

#include "Texture.h"
#include <iostream>
#include <cmath>

Texture::Texture(float r, float g, float b){
    colour = Vector3(r, g, b);
}

Texture::Texture(const char *path, float xDelta, float yDelta) : width(0), height(0), channels(0), xd(xDelta), yd(yDelta) {
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
    data = new int[width * height]{0};
    for(int i=0; i<width * height; i++){
        int index = ((i / width) * width + i % width) * 3;
        unsigned char r = image[index];
        unsigned char g = image[index+1];
        unsigned char b = image[index+2];
        data[i] = (r << 16 | g << 8 | b);
    }
    textured = true;
    stbi_image_free(image);
}

Vector3 Texture::getUV(float u, float v) {
    if(textured){
        float hee;
        u = modff(u + xd, &hee);
        v = modff(v + yd, &hee);
        int x = (int) (u * width);
        int y = (int) (v * height);
        int index = x + y * width;
        float r = data[index] >> 16 & 0x0ff;
        float g = data[index] >> 8 & 0x0ff;
        float b = data[index] >> 0 & 0x0ff;
        return Vector3(r / 255.0f, g / 255.0f, b / 255.0f);
    } else {
        return colour;
    }
}

Texture::~Texture() {
    delete(data);
}
