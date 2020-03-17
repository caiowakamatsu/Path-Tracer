//
// Created by legend on 3/17/20.
//

#include <iostream>
#include "File.h"

File::File(std::string directory, int width, int height) {
    this->directory = directory;
    this->width = width;
    this->height = height;
    this->data = nullptr;
}

File::~File() {
    delete[](data);
}

void File::setData(int * data) {
    this->data = data;
}

bool File::write() {

    /*
     * Todo: Add this code to check if the file exists, and make sure that we can specify image format and stuff
    struct stat buffer;

    bool exists = (stat("file", &buffer) == 0);
     */

    std::stringstream buffer;
    auto t = std::time(nullptr);
    buffer << std::put_time(std::localtime(&t), "%a %b %d %H:%M:%S %Y");
    std::ofstream output(directory + "/render at " + buffer.str() + ".ppm");
    output << "P3" << std::endl;
    output << width << " " << height << std::endl;
    output << "255" << std::endl;

    if(data == nullptr)
        data = new int[width * height]{0};

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int r = data[x + y * width] >> 16;
            int g = data[x + y * width] >> 8;
            int b = data[x + y * width];
            output << r << " " << g << " " << b << std::endl;
        }
    }
    return true;
}

