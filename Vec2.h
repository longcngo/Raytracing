#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

/*  Vec2.h

    A class that represents a vector of two floats, usually for texture
    coordinates.

    Everything being publc and aggressive inlining are used to ensure the class'
    operations are as fast as possible, which is inportant in a CPU intensive
    program like a Raytracer.

*/

class Vec2
{
public:
    // two elements
    float v[2];

    // constructors
    Vec2() { v[0] = 0.0f; v[1] = 0.0f; };
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
    inline Vec2& operator+=(const Vec2& vec);
    inline Vec2& operator-=(const Vec2& vec);
    inline Vec2& operator*=(const Vec2& vec);
    inline Vec2& operator/=(const Vec2& vec);
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

inline Vec2 operator+(const Vec2 &vec1, const Vec2 &vec2)
{
    return Vec2(vec1.v[0]+vec2.v[0], vec1.v[1]+vec2.v[1]);
}

inline Vec2 operator-(const Vec2 &vec1, const Vec2 &vec2)
{
    return Vec2(vec1.v[0]-vec2.v[0], vec1.v[1]-vec2.v[1]);
}

inline Vec2 operator*(const Vec2 &vec1, const Vec2 &vec2)
{
    return Vec2(vec1.v[0]*vec2.v[0], vec1.v[1]*vec2.v[1]);
}

inline Vec2 operator/(const Vec2 &vec1, const Vec2 &vec2)
{
    return Vec2(vec1.v[0]/vec2.v[0], vec1.v[1]/vec2.v[1]);
}

inline Vec2 operator*(float t, const Vec2 &vec)
{
    return Vec2(vec.v[0]*t, vec.v[1]*t);
}

inline Vec2 operator/(float t, const Vec2 &vec)
{
    return Vec2(vec.v[0]/t, vec.v[1]/t);
}

inline Vec2 operator*(const Vec2 &vec, float t)
{
    return Vec2(vec.v[0]*t, vec.v[1]*t);
}

inline Vec2 operator/(const Vec2 &vec, float t)
{
    return Vec2(vec.v[0]/t, vec.v[1]/t);
}

inline float dot(const Vec2 &vec1, const Vec2 &vec2)
{
    return vec1.v[0]*vec2.v[0] + vec1.v[1]*vec2.v[1];
}

inline Vec2& Vec2::operator+=(const Vec2 &vec)
{
    *this = *this + vec;
    return *this;
}

inline Vec2& Vec2::operator-=(const Vec2 &vec)
{
    *this = *this - vec;
    return *this;
}

inline Vec2& Vec2::operator*=(const Vec2 &vec)
{
    *this = *this * vec;
    return *this;
}

inline Vec2& Vec2::operator/=(const Vec2 &vec)
{
    *this = *this / vec;
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

inline bool operator==(const Vec2 &vec1, const Vec2 &vec2)
{
    if (vec1.v[0] != vec2.v[0]) { return false; }
    if (vec1.v[1] != vec2.v[1]) { return false; }
    return true;
}

inline bool operator!=(const Vec2 &vec1, const Vec2 &vec2)
{
    if (vec1.v[0] == vec2.v[0]) { return false; }
    if (vec1.v[1] == vec2.v[1]) { return false; }
    return true;
}

inline Vec2 unit_vector(Vec2 vec)
{
    return vec/vec.length();
}
