//
// Created by legend on 3/17/20.
//
#pragma once

class Vector3 {
public:
    float x, y, z;
    Vector3();
    Vector3(float, float, float);

    Vector3 operator + (Vector3 &a);
    void operator += (Vector3 &a);
    Vector3 operator - (Vector3 &a);
    void operator -= (Vector3 &a);
    Vector3 operator / (Vector3 &a);
    void operator /= (Vector3 &a);
    Vector3 operator * (Vector3 &a);
    void operator *= (Vector3 &a);
    Vector3 operator + (float a);
    Vector3 operator - (float a);
    Vector3 operator / (float a);
    Vector3 operator * (float t);

    void mix(Vector3&, float);
    float dot (Vector3 &a);
    float dist(Vector3 &a);
    float length();
    float lengthSq();
    Vector3 cross(Vector3 &a);
    Vector3 toUnitVector();

    void copyFrom(Vector3 *);
    void copyTo(Vector3 *);
    void copyFrom(Vector3 &);
    void copyTo(Vector3 &);
};
