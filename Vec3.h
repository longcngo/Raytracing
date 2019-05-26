#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Vec3
{
public:
    // three elements
    float x;
    float y;
    float z;

    // constructors
    Vec3() { x = 0.0f; y = 0.0f; z = 0.0f; };
    Vec3(const float xx, const float yy, const float zz)
    {
        x = xx;
        y = yy;
        z = zz;
    };

    // unary operatooers
    float operator[] (int i) const
    {
        switch (i) {
            case 0:
            return x;
            case 1:
            return y;
            case 2:
            return z;
            default:
            throw std::invalid_argument( "out of bounds value" );
        }
    }
    float& operator[] (int i)
    {
        switch (i) {
            case 0:
            return x;
            case 1:
            return y;
            case 2:
            return z;
            default:
            throw std::invalid_argument( "out of bounds value" );
        }
    }
    const Vec3& operator+() const { return *this; };
    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    // binary operators
    inline Vec3& operator+=(const Vec3& v);
    inline Vec3& operator-=(const Vec3& v);
    inline Vec3& operator*=(const Vec3& v);
    inline Vec3& operator/=(const Vec3& v);
    inline Vec3& operator*=(float t);
    inline Vec3& operator/=(float t);

    inline float squared_length() const
    {
        return x*x + y*y + z*z;
    }
    inline float length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec3 &t)
{
    is >> t.x >> t.y >> t.z;
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
    os << t.x << " " << t.y << " " << t.z;
    return os;
}

inline void Vec3::normalize()
{
    float k = 1/sqrt(x*x + y*y + z*z);
    x *= k; y *= k; z *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
}

inline Vec3 operator*(float t, const Vec3 &v)
{
    return Vec3(v.x*t, v.y*t, v.z*t);
}

inline Vec3 operator/(float t, const Vec3 &v)
{
    return Vec3(v.x/t, v.y/t, v.z/t);
}

inline Vec3 operator*(const Vec3 &v, float t)
{
    return Vec3(v.x*t, v.y*t, v.z*t);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
    return Vec3(v.x/t, v.y/t, v.z/t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3((v1.y*v2.z - v1.z*v2.y),
    (v1.z*v2.x - v1.x*v2.z),
    (v1.x*v2.y - v1.y*v2.x));
}

inline Vec3& Vec3::operator+=(const Vec3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

inline Vec3& Vec3::operator*=(float t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(float t)
{
    float k = 1/t;
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

inline Vec3 unit_vector(Vec3 v)
{
    return v/v.length();
}
