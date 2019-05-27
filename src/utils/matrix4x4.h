#pragma once

#include <string>
#include <ogc/gu.h>

// The elements of the 4x4 matrix are stored in
// row-major order.
class Matrix4x4
{
public:
    Matrix4x4(const Mtx& mtx);
    Matrix4x4(const Mtx44& mtx);

    std::string ToString() const;

    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};
