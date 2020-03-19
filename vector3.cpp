//
// Created by legend on 3/17/20.
//

#include <cmath>
#include "vector3.h"

vector3::vector3(){
    vector3(0, 0, 0);
}

vector3::vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vector3 vector3::operator+(vector3 &a) {
    return vector3(x + a.x,y + a.y,z + a.z);
}

vector3 vector3::operator-(vector3 &a) {
    return vector3(x - a.x,y - a.y,z - a.z);
}

vector3 vector3::operator/(vector3 &a) {
    return vector3(x / a.x, y / a.y, z / a.z);
}

vector3 vector3::operator*(vector3 &a) {
    return vector3(x * a.x,y * a.y,z * a.z);
}

vector3 vector3::operator*(float t) {
    return vector3(x * t, y * t, z * t);
}

float vector3::dot(vector3 &a) {
    return x * a.x + y * a.y + z * a.z;
}

float vector3::length() {
    return sqrtf(lengthSq());
}

float vector3::lengthSq() {
    return x * x + y * y + z * z;
}

vector3 vector3::cross(vector3 &a) {
    return vector3(
            y * a.z - z * a.z,
            z * a.x - x * a.z,
            x * a.y - y * a.x);
}

vector3 vector3::toUnitVector() {
    float t = length();
    return vector3(x / t, y / t, z / t);
}

