#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Vec2
{
public:
    // two elements
    float x;
    float y;

    // constructors
    Vec2() { x = 0.0f; y = 0.0f; };
    Vec2(const float xx, const float yy)
    {
        x = xx;
        y = yy;
    };

    // unary operatooers
    float operator[] (int i) const
    {
        switch (i) {
            case 0:
            return x;
            case 1:
            return y;
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
            default:
            throw std::invalid_argument( "out of bounds value" );
        }
    }
    const Vec2& operator+() const { return *this; };
    Vec2 operator-() const { return Vec2(-x, -y); }

    // binary operators
    inline Vec2& operator+=(const Vec2& v);
    inline Vec2& operator-=(const Vec2& v);
    inline Vec2& operator*=(const Vec2& v);
    inline Vec2& operator/=(const Vec2& v);
    inline Vec2& operator*=(float t);
    inline Vec2& operator/=(float t);

    inline float squared_length() const
    {
        return x*x + y*y;
    }
    inline float length() const
    {
        return sqrt(x*x + y*y);
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec2 &t)
{
    is >> t.x >> t.y;
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec2 &t)
{
    os << t.x << " " << t.y;
    return os;
}

inline void Vec2::normalize()
{
    float k = 1/sqrt(x*x + y*y);
    x *= k; y *= k;
}

inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x+v2.x, v1.y+v2.y);
}

inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x-v2.x, v1.y-v2.y);
}

inline Vec2 operator*(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x*v2.x, v1.y*v2.y);
}

inline Vec2 operator/(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x/v2.x, v1.y/v2.y);
}

inline Vec2 operator*(float t, const Vec2 &v)
{
    return Vec2(v.x*t, v.y*t);
}

inline Vec2 operator/(float t, const Vec2 &v)
{
    return Vec2(v.x/t, v.y/t);
}

inline Vec2 operator*(const Vec2 &v, float t)
{
    return Vec2(v.x*t, v.y*t);
}

inline Vec2 operator/(const Vec2 &v, float t)
{
    return Vec2(v.x/t, v.y/t);
}

inline float dot(const Vec2 &v1, const Vec2 &v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

inline Vec2& Vec2::operator+=(const Vec2 &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

inline Vec2& Vec2::operator-=(const Vec2 &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

inline Vec2& Vec2::operator*=(const Vec2 &v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

inline Vec2& Vec2::operator/=(const Vec2 &v)
{
    x /= v.x;
    y /= v.y;
    return *this;
}

inline Vec2& Vec2::operator*=(float t)
{
    x *= t;
    y *= t;
    return *this;
}

inline Vec2& Vec2::operator/=(float t)
{
    float k = 1/t;
    x *= k;
    y *= k;
    return *this;
}

inline Vec2 unit_vector(Vec2 v)
{
    return v/v.length();
}
