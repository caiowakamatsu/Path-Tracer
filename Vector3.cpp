//
// Created by legend on 3/17/20.
//

#include <cmath>
#include "Vector3.h"

Vector3::Vector3(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(Vector3 &a) {
    return Vector3(x + a.x, y + a.y, z + a.z);
}

void Vector3::operator+=(Vector3 &a) {
    x += a.x;
    y += a.y;
    z += a.z;
}

Vector3 Vector3::operator-(Vector3 &a) {
    return Vector3(x - a.x, y - a.y, z - a.z);
}

void Vector3::operator-=(Vector3 &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
}

Vector3 Vector3::operator/(Vector3 &a) {
    return Vector3(x / a.x, y / a.y, z / a.z);
}

void Vector3::operator/=(Vector3 &a) {
    x /= a.x;
    y /= a.y;
    z /= a.z;
}

Vector3 Vector3::operator*(Vector3 &a) {
    return Vector3(x * a.x, y * a.y, z * a.z);
}

void Vector3::operator*=(Vector3 &a) {
    x *= a.x;
    y *= a.y;
    z *= a.z;
}

Vector3 Vector3::operator+(float a) {
    return Vector3(x + a, y + a, z + a);
}

Vector3 Vector3::operator-(float a) {
    return Vector3(x - a, y - a, z - a);
}

Vector3 Vector3::operator/(float a) {
    return Vector3(x / a, y / a, z / a);
}

Vector3 Vector3::operator*(float t) {
    return Vector3(x * t, y * t, z * t);
}

void Vector3::mix(Vector3& a, float t){
    x = x + (a.x - x) * t;
    y = y + (a.y - y) * t;
    z = z + (a.z - z) * t;
}

float Vector3::dot(Vector3 &a) {
    return x * a.x + y * a.y + z * a.z;
}

float Vector3::dist(Vector3 &a) {
    return sqrtf(powf(x - a.x, 2) + powf(y * a.y, 2) + powf(z * a.z, 2));
}

float Vector3::length() {
    return sqrtf(lengthSq());
}

float Vector3::lengthSq() {
    return x * x + y * y + z * z;
}

Vector3 Vector3::cross(Vector3 &a) {
    return Vector3(
            y * a.z - z * a.z,
            z * a.x - x * a.z,
            x * a.y - y * a.x);
}

Vector3 Vector3::toUnitVector() {
    float t = length();
    return Vector3(x / t, y / t, z / t);
}

void Vector3::copyFrom(Vector3 * from) {
    x = (*from).x;
    y = (*from).y;
    z = (*from).z;
}

void Vector3::copyTo(Vector3 * to) {
    (*to).x = x;
    (*to).y = y;
    (*to).z = z;
}

void Vector3::copyFrom(Vector3 & from) {
    x = from.x;
    y = from.y;
    z = from.z;
}

void Vector3::copyTo(Vector3 & to) {
    to.x = x;
    to.y = y;
    to.z = z;
}

