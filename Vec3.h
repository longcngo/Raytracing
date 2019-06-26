#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

/*  Vec3.h

    A class that represents a vector of three floats, usually points in space or
    directions.

    Everything being publc and aggressive inlining are used to ensure the class'
    operations are as fast as possible, which is inportant in a CPU intensive
    program like a Raytracer.

*/

class Vec3
{
public:
    // three elements
    float v[3];

    // constructors
    Vec3() { v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; };
    Vec3(const float xx, const float yy, const float zz)
    {
        v[0] = xx;
        v[1] = yy;
        v[2] = zz;
    };

    // unary operaters
    float operator[] (int i) const { return v[i]; }
    float& operator[] (int i) { return v[i]; }
    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
    const Vec3& operator+() const { return *this; };
    Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }

    // binary operators
    inline Vec3& operator+=(const Vec3& vec);
    inline Vec3& operator-=(const Vec3& vec);
    inline Vec3& operator*=(const Vec3& vec);
    inline Vec3& operator/=(const Vec3& vec);
    inline Vec3& operator*=(float t);
    inline Vec3& operator/=(float t);

    inline float squared_length() const
    {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }
    inline float length() const
    {
        return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec3 &t)
{
    is >> t.v[0] >> t.v[1] >> t.v[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
    os << t.v[0] << " " << t.v[1] << " " << t.v[2];
    return os;
}

inline void Vec3::normalize()
{
    float k = 1/sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= k; v[1] *= k; v[2] *= k;
}

inline Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.v[0]+vec2.v[0], vec1.v[1]+vec2.v[1], vec1.v[2]+vec2.v[2]);
}

inline Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.v[0]-vec2.v[0], vec1.v[1]-vec2.v[1], vec1.v[2]-vec2.v[2]);
}

inline Vec3 operator*(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.v[0]*vec2.v[0], vec1.v[1]*vec2.v[1], vec1.v[2]*vec2.v[2]);
}

inline Vec3 operator/(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.v[0]/vec2.v[0], vec1.v[1]/vec2.v[1], vec1.v[2]/vec2.v[2]);
}

inline Vec3 operator*(float t, const Vec3 &vec)
{
    return Vec3(vec.v[0]*t, vec.v[1]*t, vec.v[2]*t);
}

inline Vec3 operator/(float t, const Vec3 &vec)
{
    return Vec3(vec.v[0]/t, vec.v[1]/t, vec.v[2]/t);
}

inline Vec3 operator*(const Vec3 &vec, float t)
{
    return Vec3(vec.v[0]*t, vec.v[1]*t, vec.v[2]*t);
}

inline Vec3 operator/(const Vec3 &vec, float t)
{
    return Vec3(vec.v[0]/t, vec.v[1]/t, vec.v[2]/t);
}

inline float dot(const Vec3 &vec1, const Vec3 &vec2)
{
    return vec1.v[0]*vec2.v[0] + vec1.v[1]*vec2.v[1] + vec1.v[2]*vec2.v[2];
}

inline Vec3 cross(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3((vec1.v[1]*vec2.v[2] - vec1.v[2]*vec2.v[1]),
    (vec1.v[2]*vec2.v[0] - vec1.v[0]*vec2.v[2]),
    (vec1.v[0]*vec2.v[1] - vec1.v[1]*vec2.v[0]));
}

inline Vec3& Vec3::operator+=(const Vec3 &vec)
{
    *this = *this + vec;
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &vec)
{
    *this = *this - vec;
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &vec)
{
    *this = *this * vec;
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &vec)
{
    *this = *this / vec;
    return *this;
}

inline Vec3& Vec3::operator*=(float t)
{
    *this = *this * t;
    return *this;
}

inline Vec3& Vec3::operator/=(float t)
{
    float k = 1/t;
    *this = *this * k;
    return *this;
}

inline bool operator==(const Vec3 &vec1, const Vec3 &vec2)
{
    if (vec1.v[0] != vec2.v[0]) { return false; }
    if (vec1.v[1] != vec2.v[1]) { return false; }
    if (vec1.v[2] != vec2.v[2]) { return false; }
    return true;
}

inline bool operator!=(const Vec3 &vec1, const Vec3 &vec2)
{
    if (vec1.v[0] == vec2.v[0]) { return false; }
    if (vec1.v[1] == vec2.v[1]) { return false; }
    if (vec1.v[2] == vec2.v[2]) { return false; }
    return true;
}

inline Vec3 unit_vector(Vec3 vec)
{
    return vec/vec.length();
}
