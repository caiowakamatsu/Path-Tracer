//
// Created by legend on 5/25/20.
//

#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include "Triangle.h"
#include "World.h"

class World;

class ModelLoader {
public:
    void loadModel(const char* path, World& world);
private:
    std::vector<std::string> split(std::string& string, std::string& split);
};


