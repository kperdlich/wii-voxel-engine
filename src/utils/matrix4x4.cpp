#include "matrix4x4.h"
#include <sstream>

Matrix4x4::Matrix4x4(const Mtx& mtx)
{
    _11 = mtx[0][0];
    _12 = mtx[0][1];
    _13 = mtx[0][2];
    _14 = mtx[0][3];

    _21 = mtx[1][0];
    _22 = mtx[1][1];
    _23 = mtx[1][2];
    _24 = mtx[1][3];

    _31 = mtx[2][0];
    _32 = mtx[2][1];
    _33 = mtx[2][2];
    _34 = mtx[2][3];

    _41 = 0.0f;
    _42 = 0.0f;
    _43 = 0.0f;
    _44 = 0.0f;
}

Matrix4x4::Matrix4x4(const Mtx44 &mtx)
{
    _11 = mtx[0][0];
    _12 = mtx[0][1];
    _13 = mtx[0][2];
    _14 = mtx[0][3];

    _21 = mtx[1][0];
    _22 = mtx[1][1];
    _23 = mtx[1][2];
    _24 = mtx[1][3];

    _31 = mtx[2][0];
    _32 = mtx[2][1];
    _33 = mtx[2][2];
    _34 = mtx[2][3];

    _41 = mtx[3][0];
    _42 = mtx[3][1];
    _43 = mtx[3][2];
    _44 = mtx[3][3];
}

std::string Matrix4x4::ToString() const
{
    std::stringstream ss;
    ss << "11: " << _11;
    ss << " 12: " << _12;
    ss << " 13: " << _13;
    ss << " 14: " << _14 << std::endl;

    ss << "21: " << _21;
    ss << " 22: " << _22;
    ss << " 23: " << _23;
    ss << " 24: " << _24 << std::endl;

    ss << "31: " << _31;
    ss << " 32: " << _32;
    ss << " 33: " << _33;
    ss << " 34: " << _34 << std::endl;

    ss << "41: " << _41;
    ss << " 42: " << _42;
    ss << " 43: " << _43;
    ss << " 44: " << _44 << std::endl;
    return ss.str();
}
