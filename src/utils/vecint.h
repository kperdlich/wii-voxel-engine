#ifndef VEC2_H
#define VEC2_H

#include <stdint.h>

struct Vec3i
{
    uint32_t X;
    uint32_t Y;
    uint32_t Z;
};

struct Vec2i
{
    int32_t X;
    int32_t Y;
    Vec2i(int32_t x = 0, int32_t y = 0) : X(x), Y(y) {}

    bool operator==(const Vec2i &vec) const
    {
        return (X == vec.X) && (Y == vec.Y);
    }

    bool operator!=(const Vec2i &vec) const
    {
        return (X != vec.X) || (Y != vec.Y);
    }
};

#endif // VEC2_H
