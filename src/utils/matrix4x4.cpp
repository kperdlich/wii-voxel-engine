#include <sstream>
#include <cstring>
#include "utils/matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    std::memset(matrix, 0, sizeof(matrix));
}

Matrix4x4::Matrix4x4(const Mtx& mtx)
{
    matrix[0][0] = mtx[0][0];
    matrix[0][1] = mtx[0][1];
    matrix[0][2] = mtx[0][2];
    matrix[0][3] = mtx[0][3];

    matrix[1][0] = mtx[1][0];
    matrix[1][1] = mtx[1][1];
    matrix[1][2] = mtx[1][2];
    matrix[1][3] = mtx[1][3];

    matrix[2][0] = mtx[2][0];
    matrix[2][1] = mtx[2][1];
    matrix[2][2] = mtx[2][2];
    matrix[2][3] = mtx[2][3];

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 0.0f;
}

Matrix4x4::Matrix4x4(const Mtx44& mtx)
{
    matrix[0][0] = mtx[0][0];
    matrix[0][1] = mtx[0][1];
    matrix[0][2] = mtx[0][2];
    matrix[0][3] = mtx[0][3];

    matrix[1][0] = mtx[1][0];
    matrix[1][1] = mtx[1][1];
    matrix[1][2] = mtx[1][2];
    matrix[1][3] = mtx[1][3];

    matrix[2][0] = mtx[2][0];
    matrix[2][1] = mtx[2][1];
    matrix[2][2] = mtx[2][2];
    matrix[2][3] = mtx[2][3];

    matrix[3][0] = mtx[3][0];
    matrix[3][1] = mtx[3][1];
    matrix[3][2] = mtx[3][2];
    matrix[3][3] = mtx[3][3];
}


std::string Matrix4x4::ToString() const
{
	std::stringstream ss;
    ss << matrix[0][0] << " "
    << matrix[0][1] << " "
    << matrix[0][2] << " "
    << matrix[0][3] << std::endl;

    ss << matrix[1][0] << " "
    << matrix[1][1] << " "
    << matrix[1][2] << " "
    << matrix[1][3] << std::endl;

    ss << matrix[2][0] << " "
    << matrix[2][1] << " "
    << matrix[2][2] << " "
    << matrix[2][3] << std::endl;

    ss << matrix[3][0] << " "
    << matrix[3][1] << " "
    << matrix[3][2] << " "
    << matrix[3][3] << std::endl;
	return ss.str();
}
