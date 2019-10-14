#pragma once

#include <string>
#include <ogc/gu.h>

// The elements of the 4x4 matrix are stored in
// row-major order.
class Matrix4x4
{
public:
    Matrix4x4();
	Matrix4x4(const Mtx& mtx);
	Matrix4x4(const Mtx44& mtx);

    Matrix4x4(const Matrix4x4&) = default;
    Matrix4x4(Matrix4x4&&) = default;
    Matrix4x4& operator=(const Matrix4x4&) = default;
    Matrix4x4& operator=(Matrix4x4&&) = default;

    inline void SetIdentity();
	std::string ToString() const;    

    inline Matrix4x4 operator+(const Matrix4x4& other) const;
    inline Matrix4x4 operator*(const Matrix4x4& other) const;
    inline Matrix4x4 operator*(float value) const;
    inline void operator+=(const Matrix4x4& other);
    inline void operator*=(const Matrix4x4& other);
    inline bool operator==(const Matrix4x4& other) const;
    inline bool operator!=(const Matrix4x4& other) const;

private:
    float matrix[4][4];
};

inline void Matrix4x4::SetIdentity()
{
    matrix[0][0] = 1; matrix[0][1] = 0;  matrix[0][2] = 0;  matrix[0][3] = 0;
    matrix[1][0] = 0; matrix[1][1] = 1;  matrix[1][2] = 0;  matrix[1][3] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0;  matrix[2][2] = 1;  matrix[2][3] = 0;
    matrix[3][0] = 0; matrix[3][1] = 0;  matrix[3][2] = 0;  matrix[3][3] = 1;
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
    Matrix4x4 result;
    for (uint32_t x = 0; x < 4; ++x)
    {
        for (uint32_t y = 0; y < 4; ++y)
        {
            result.matrix[x][y] = matrix[x][y] + other.matrix[x][y];
        }
    }
    return result;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
    Matrix4x4 result;
    for(uint32_t i = 0; i < 4; ++i)
    {
        for(uint32_t j = 0; j < 4; ++j)
        {
            for(uint32_t k = 0; k < 4; ++k)
            {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return result;
}

inline Matrix4x4 Matrix4x4::operator*(float value) const
{
    Matrix4x4 result;
    for (uint32_t x = 0; x < 4; ++x)
    {
        for (uint32_t y = 0; y < 4; ++y)
        {
            result.matrix[x][y] = matrix[x][y] * value;
        }
    }
    return result;
}

inline void Matrix4x4::operator+=(const Matrix4x4& other)
{
    *this = *this + other;
}

inline void Matrix4x4::operator*=(const Matrix4x4& other)
{
    *this = *this * other;
}

inline bool Matrix4x4::operator==(const Matrix4x4& other) const
{
    for (uint32_t x = 0; x < 4; ++x)
    {
        for (uint32_t y = 0; y < 4; ++y)
        {
            if (matrix[x][y] != other.matrix[x][y]) // maybe add a equals method with a custom tolerance?
            {
                return false;
            }
        }
    }
    return true;
}

inline bool Matrix4x4::operator!=(const Matrix4x4& other) const
{
    return !(*this == other);
}
