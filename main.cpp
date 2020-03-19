#include <iostream>
#include "File.h"

constexpr int WIDTH = 255, HEIGHT = 255;

int main() {
    File file("../renders", WIDTH, HEIGHT);
    int * pixels = new int[WIDTH * HEIGHT]{0};

    

    file.setData(pixels);
    file.write();
    return 0;
}