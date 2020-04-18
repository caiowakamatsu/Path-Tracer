//
// Created by legend on 4/14/20.
//

#include "Texture.h"
#include <iostream>

Texture::Texture(char *path) : width(0), height(0), channels(0) {
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
    data = new int[width * height]{0};
    std::cout << width * height << std::endl;
    for(int i=0; i<width * height; i++){
        int index = ((i / width) * width + i % width) * 3;
        int r = (int) image[index];
        int g = (int) image[index+1];
        int b = (int) image[index+2];
        data[i] = (r << 16 | g << 8 | b) ^ 0x00ffffff;
    }
    stbi_image_free(image);
}

Vector3 Texture::getUV(float u, float v) {
int x = (int) (u * width);
    int y = (int) (v * height);
//    int index = 0;
    int index = x + y * width;
//    std::cout << "Width: " << width << ", Height: " << height << std::endl;
    int r = data[index] >> 16 & 0x0ff;
    int g = data[index] >> 8 & 0x0ff;
    int b = data[index] >> 0 & 0x0ff;
    return Vector3(r, g, b);
}

Texture::~Texture() {
    delete(data);
}
