//
// Created by legend on 3/17/20.
//
#pragma once

class Vector3 {
public:
    float x, y, z;
    Vector3();
    Vector3(float, float, float);

    inline Vector3 operator + (Vector3 &a);
    inline Vector3 operator - (Vector3 &a);
    inline Vector3 operator / (Vector3 &a);
    inline Vector3 operator * (Vector3 &a);
    inline Vector3 operator * (float t);

    inline float dot (Vector3 &a);
    inline float length();
    inline float lengthSq();
    inline Vector3 cross(Vector3 &a);
    inline Vector3 toUnitVector();
};
