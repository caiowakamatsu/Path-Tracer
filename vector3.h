//
// Created by legend on 3/17/20.
//
#pragma once

class vector3 {
public:
    float x, y, z;
    vector3();
    vector3(float, float, float);

    inline vector3 operator + (vector3 &a);
    inline vector3 operator - (vector3 &a);
    inline vector3 operator / (vector3 &a);
    inline vector3 operator * (vector3 &a);
    inline vector3 operator * (float t);

    inline float dot (vector3 &a);
    inline float length();
    inline float lengthSq();
    inline vector3 cross(vector3 &a);
    inline vector3 toUnitVector();
};
