#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Vec2
{
public:
    // two elements
    float v[2];

    // constructors
    Vec2() { v[0] = v[1] = 0.0f; };
    Vec2(const float xx, const float yy)
    {
        v[0] = xx;
        v[1] = yy;
    };

    // unary operatooers
    float operator[] (int i) const { return v[i]; }
    float& operator[] (int i) { return v[i]; }
    float x() const { return v[0]; }
    float y() const { return v[1]; }
    const Vec2& operator+() const { return *this; };
    Vec2 operator-() const { return Vec2(-v[0], -v[1]); }

    // binary operators
    inline Vec2& operator+=(const Vec2& v);
    inline Vec2& operator-=(const Vec2& v);
    inline Vec2& operator*=(const Vec2& v);
    inline Vec2& operator/=(const Vec2& v);
    inline Vec2& operator*=(float t);
    inline Vec2& operator/=(float t);

    inline float squared_length() const
    {
        return v[0]*v[0] + v[1]*v[1];
    }
    inline float length() const
    {
        return sqrt(v[0]*v[0] + v[1]*v[1]);
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec2 &t)
{
    is >> t.v[0] >> t.v[1];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec2 &t)
{
    os << t.v[0] << " " << t.v[1];
    return os;
}

inline void Vec2::normalize()
{
    float k = 1/sqrt(v[0]*v[0] + v[1]*v[1]);
    v[0] *= k; v[1] *= k;
}

inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.v[0]+v2.v[0], v1.v[1]+v2.v[1]);
}

inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.v[0]-v2.v[0], v1.v[1]-v2.v[1]);
}

inline Vec2 operator*(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.v[0]*v2.v[0], v1.v[1]*v2.v[1]);
}

inline Vec2 operator/(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.v[0]/v2.v[0], v1.v[1]/v2.v[1]);
}

inline Vec2 operator*(float t, const Vec2 &v)
{
    return Vec2(v.v[0]*t, v.v[1]*t);
}

inline Vec2 operator/(float t, const Vec2 &v)
{
    return Vec2(v.v[0]/t, v.v[1]/t);
}

inline Vec2 operator*(const Vec2 &v, float t)
{
    return Vec2(v.v[0]*t, v.v[1]*t);
}

inline Vec2 operator/(const Vec2 &v, float t)
{
    return Vec2(v.v[0]/t, v.v[1]/t);
}

inline float dot(const Vec2 &v1, const Vec2 &v2)
{
    return v1.v[0]*v2.v[0] + v1.v[1]*v2.v[1];
}

inline Vec2& Vec2::operator+=(const Vec2 &v)
{
    *this = *this + v;
    return *this;
}

inline Vec2& Vec2::operator-=(const Vec2 &v)
{
    *this = *this - v;
    return *this;
}

inline Vec2& Vec2::operator*=(const Vec2 &v)
{
    *this = *this * v;
    return *this;
}

inline Vec2& Vec2::operator/=(const Vec2 &v)
{
    *this = *this / v;
    return *this;
}

inline Vec2& Vec2::operator*=(float t)
{
    *this = *this * t;
    return *this;
}

inline Vec2& Vec2::operator/=(float t)
{
    float k = 1/t;
    *this = *this * k;
    return *this;
}

inline bool operator==(const Vec2 &v1, const Vec2 &v2)
{
    if (v1.v[0] != v2.v[0]) { return false; }
    if (v1.v[1] != v2.v[1]) { return false; }
    return true;
}

inline bool operator!=(const Vec2 &v1, const Vec2 &v2)
{
    if (v1.v[0] == v2.v[0]) { return false; }
    if (v1.v[1] == v2.v[1]) { return false; }
    return true;
}

inline Vec2 unit_vector(Vec2 v)
{
    return v/v.length();
}
