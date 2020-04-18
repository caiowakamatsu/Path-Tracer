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

const Vector3 Vector3::operator+(const Vector3 &a) const {
    return Vector3(x + a.x, y + a.y, z + a.z);
}

void Vector3::operator+=(const Vector3 &a) {
    x += a.x;
    y += a.y;
    z += a.z;
}

const Vector3 Vector3::operator-(const Vector3 &a) const {
    return Vector3(x - a.x, y - a.y, z - a.z);
}

void Vector3::operator-=(const Vector3 &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
}

const Vector3 Vector3::operator/(const Vector3 &a) const {
    return Vector3(x / a.x, y / a.y, z / a.z);
}

void Vector3::operator/=(const Vector3 &a) {
    x /= a.x;
    y /= a.y;
    z /= a.z;
}

const Vector3 Vector3::operator*(const Vector3 &a) const {
    return Vector3(x * a.x, y * a.y, z * a.z);
}

void Vector3::operator*=(const Vector3 &a) {
    x *= a.x;
    y *= a.y;
    z *= a.z;
}

const Vector3 Vector3::operator+(float a) const {
    return Vector3(x + a, y + a, z + a);
}

const Vector3 Vector3::operator-(float a) const {
    return Vector3(x - a, y - a, z - a);
}

const Vector3 Vector3::operator/(float a) const {
    return Vector3(x / a, y / a, z / a);
}

const Vector3 Vector3::operator*(float t) const {
    return Vector3(x * t, y * t, z * t);
}

void Vector3::mix(const Vector3& a, float t){
    x = x + (a.x - x) * t;
    y = y + (a.y - y) * t;
    z = z + (a.z - z) * t;
}

const Vector3 Vector3::reflect(const Vector3& a) const {
    Vector3 b = a * 2.0 * dot(a);
    return *this - b;
}

void Vector3::refract(const Vector3 &a, float t) {
    Vector3 unit = toUnitVector();
    float dot = unit.dot(a);
    float disc = 1.0f - t * t * (1.0 - dot * dot);
    Vector3 other = a * sqrtf(disc);
    Vector3 ret = (a * dot);
    ret -= a;
    ret = ret * t;
    *this = disc > 0.0f ? ret - other : Vector3();
}

float Vector3::dot(const Vector3 &a) const {
    return x * a.x + y * a.y + z * a.z;
}


float Vector3::dist(const Vector3 &a) const {
    return sqrtf(powf(x - a.x, 2) + powf(y * a.y, 2) + powf(z * a.z, 2));
}

float Vector3::length() const {
    return sqrtf(lengthSq());
}

float Vector3::lengthSq() const {
    return x * x + y * y + z * z;
}

const Vector3 Vector3::cross(const Vector3 &a) const {
    return Vector3(
            y * a.z - z * a.z,
            z * a.x - x * a.z,
            x * a.y - y * a.x);
}

const Vector3 Vector3::toUnitVector() const {
    float t = length();
    return Vector3(x / t, y / t, z / t);
}
