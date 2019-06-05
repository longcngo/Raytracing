#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Vec3
{
public:
    // three elements
    float v[3];

    // constructors
    Vec3() { v[0] = v[1] = v[2] = 0; };
    Vec3(const float xx, const float yy, const float zz)
    {
        v[0] = xx;
        v[1] = yy;
        v[2] = zz;
    };

    // unary operatooers
    float operator[] (int i) const { return v[i]; }
    float& operator[] (int i) { return v[i]; }
    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
    const Vec3& operator+() const { return *this; };
    Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }

    // binary operators
    inline Vec3& operator+=(const Vec3& v);
    inline Vec3& operator-=(const Vec3& v);
    inline Vec3& operator*=(const Vec3& v);
    inline Vec3& operator/=(const Vec3& v);
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

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.v[0]+v2.v[0], v1.v[1]+v2.v[1], v1.v[2]+v2.v[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.v[0]-v2.v[0], v1.v[1]-v2.v[1], v1.v[2]-v2.v[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.v[0]*v2.v[0], v1.v[1]*v2.v[1], v1.v[2]*v2.v[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.v[0]/v2.v[0], v1.v[1]/v2.v[1], v1.v[2]/v2.v[2]);
}

inline Vec3 operator*(float t, const Vec3 &v)
{
    return Vec3(v.v[0]*t, v.v[1]*t, v.v[2]*t);
}

inline Vec3 operator/(float t, const Vec3 &v)
{
    return Vec3(v.v[0]/t, v.v[1]/t, v.v[2]/t);
}

inline Vec3 operator*(const Vec3 &v, float t)
{
    return Vec3(v.v[0]*t, v.v[1]*t, v.v[2]*t);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
    return Vec3(v.v[0]/t, v.v[1]/t, v.v[2]/t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2)
{
    return v1.v[0]*v2.v[0] + v1.v[1]*v2.v[1] + v1.v[2]*v2.v[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3((v1.v[1]*v2.v[2] - v1.v[2]*v2.v[1]),
    (v1.v[2]*v2.v[0] - v1.v[0]*v2.v[2]),
    (v1.v[0]*v2.v[1] - v1.v[1]*v2.v[0]));
}

inline Vec3& Vec3::operator+=(const Vec3 &v)
{
    *this = *this + v;
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v)
{
    *this = *this - v;
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v)
{
    *this = *this * v;
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v)
{
    *this = *this / v;
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

inline bool operator==(const Vec3 &v1, const Vec3 &v2)
{
    if (v1.v[0] != v2.v[0]) { return false; }
    if (v1.v[1] != v2.v[1]) { return false; }
    if (v1.v[2] != v2.v[2]) { return false; }
    return true;
}

inline bool operator!=(const Vec3 &v1, const Vec3 &v2)
{
    if (v1.v[0] == v2.v[0]) { return false; }
    if (v1.v[1] == v2.v[1]) { return false; }
    if (v1.v[2] == v2.v[2]) { return false; }
    return true;
}

inline Vec3 unit_vector(Vec3 v)
{
    return v/v.length();
}
