//
// Created by legend on 3/17/20.
//
#pragma once

class Vector3 {
public:
    float x, y, z;
    Vector3();
    Vector3(float, float, float);

    const Vector3 operator + (const Vector3 &a) const;
    void operator += (const Vector3 &a);
    const Vector3 operator - (const Vector3 &a) const;
    void operator -= (const Vector3 &a);
    const Vector3 operator / (const Vector3 &a) const;
    void operator /= (const Vector3 &a);
    const Vector3 operator * (const Vector3 &a) const;
    void operator *= (const Vector3 &a);
    const Vector3 operator + (float a) const;
    const Vector3 operator - (float a) const;
    const Vector3 operator / (float a) const;
    const Vector3 operator * (float t) const;

    void mix(const Vector3&, float);
    void refract(const Vector3&, float);
    float dot (const Vector3 &a) const;
    float dist(const Vector3 &a) const;
    float length() const;
    float lengthSq() const;
    const Vector3 cross(const Vector3 &a) const;
    const Vector3 toUnitVector() const;
    const Vector3 reflect(const Vector3&) const;
};
