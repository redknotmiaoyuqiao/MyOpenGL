//
// Created by redknot on 8/12/16.
//

#include "Vector3f.h"
#include <math.h>


Vector3f::Vector3f()
{

}

Vector3f::Vector3f(float _x,float _y,float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3f Vector3f::Cross(Vector3f& v)
{
    float _x = y * v.z - z * v.y;
    float _y = z * v.x - x * v.z;
    float _z = x * v.y - y * v.x;

    return Vector3f(_x,_y,_z);
}

Vector3f& Vector3f::Normalize()
{
    const float Length = sqrtf(x * x + y * y + z * z);
    x /= Length;
    y /= Length;
    z /= Length;

    return *this;
}