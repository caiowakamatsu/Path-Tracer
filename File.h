//
// Created by legend on 3/17/20.
//
#pragma once
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

class File {
private:
    int width, height;
    int * data;
    std::string directory;
public:
    File(std::string, int, int);
    ~File();
    void setData(int *);
    bool write();
};
