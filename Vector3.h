//
// Created by legend on 3/17/20.
//
#pragma once

class Vector3 {
public:
    float x, y, z;
    Vector3();
    Vector3(float, float, float);

    const Vector3 operator + (Vector3 &a) const;
    void operator += (Vector3 &a);
    const Vector3 operator - (Vector3 &a) const;
    void operator -= (Vector3 &a);
    const Vector3 operator / (Vector3 &a) const;
    void operator /= (Vector3 &a);
    const Vector3 operator * (Vector3 &a) const;
    void operator *= (Vector3 &a);
    const Vector3 operator + (float a) const;
    const Vector3 operator - (float a) const;
    const Vector3 operator / (float a) const;
    const Vector3 operator * (float t) const;

    void mix(Vector3&, float);
    void refract(Vector3&, float);
    float dot (Vector3 &a) const;
    float dist(Vector3 &a) const;
    float length() const;
    float lengthSq() const;
    const Vector3 cross(Vector3 &a) const;
    const Vector3 toUnitVector() const;
    const Vector3 reflect(Vector3&) const;

    void copyFrom(Vector3 *);
    void copyTo(Vector3 *);
    void copyFrom(Vector3 &);
    void copyTo(Vector3 &);
};
