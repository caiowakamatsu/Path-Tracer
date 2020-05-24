//
// Created by legend on 5/25/20.
//

#include "ModelLoader.h"
#include "NormalMat.h"

void ModelLoader::loadModel(const char *path, World& world) {
    std::fstream file(path);
    if (!file.is_open())
        std::cerr << "Error loading model [" << path << "] couldn't open";
    std::string string;
    const char* strPtr;
    std::vector<Vector3> vertices;
    std::vector<Vector3> textureCoords;
    while (std::getline(file, string)) {
        strPtr = string.c_str();
        std::string currentString;
        std::string splitter = " ";
        switch (string[0]) {
            case 'v':
                switch (string[1]) {
                    case ' ': {
                        strPtr += 2;
                        currentString.append(strPtr, string.size() - 2);
                        std::vector<std::string> nums = split(currentString, splitter);
                        Vector3 vector;
                        for(int i=0; i<3; i++){
                            vector[i] = std::stof(nums[i]);
                        }
                        vertices.push_back(vector);
                    }
                        break;
                    case 't': {
                        strPtr += 2;
                        currentString.append(strPtr, string.size() - 2);
                        std::vector<std::string> nums = split(currentString, splitter);
                        Vector3 vector;
                        for(int i=0; i<2; i++){
                            vector[i] = std::stof(nums[i]);
                        }
                        textureCoords.push_back(vector);
                    }
                        break;
                }
                break;
            case 'f': {
                strPtr++;
                currentString.append(strPtr, string.size() - 1);
                std::vector<std::string> faceVertices = split(currentString, splitter);
                std::string vertexSplitter = std::string("/");
                auto* triangle = new Triangle();
                for(int i=0; i<3; i++){
                    std::vector<std::string> vertexInformation = split(faceVertices[i], vertexSplitter);
                    Vector3 vector = vertices[std::atoi(vertexInformation[0].c_str()) - 1];
                    Vector3 uv = textureCoords[std::atoi(vertexInformation[0].c_str()) - 1];
                    triangle->vertices[i].pos = vector;
                    triangle->vertices[i].u = uv.x;
                    triangle->vertices[i].v = uv.y;
                }
                triangle->material = new NormalMat(true);
                triangle->calculateNormal();
                world.addTriangle(triangle);
            }
                break;
        }
    }
}

std::vector<std::string> ModelLoader::split(std::string &str, std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

