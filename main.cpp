#include <iostream>
#include "File.h"

constexpr int WIDTH = 255, HEIGHT = 255;

int main() {
    File file("../renders", WIDTH, HEIGHT);
    int * pixels = new int[WIDTH * HEIGHT]{0};

    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            pixels[x + y * WIDTH] = ((255&0x0ff)<<16)|((0&0x0ff)<<8)|(0&0x0ff);
        }
    }

    file.setData(pixels);
    file.write();
    return 0;
}