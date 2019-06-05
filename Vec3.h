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
    float x() { return v[0]; }
    float y() { return v[1]; }
    float z() { return v[2]; }
    const Vec3& operator+() const { return *this; };
    Vec3 operator-() const { return Vec3(-x(), -y(), -z()); }

    // binary operators
    inline Vec3& operator+=(const Vec3& v);
    inline Vec3& operator-=(const Vec3& v);
    inline Vec3& operator*=(const Vec3& v);
    inline Vec3& operator/=(const Vec3& v);
    inline Vec3& operator*=(float t);
    inline Vec3& operator/=(float t);

    inline float squared_length() const
    {
        return x()*x() + y()*y() + z()*z();
    }
    inline float length() const
    {
        return sqrt(x()*x() + y()*y() + z()*z());
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec3 &t)
{
    is >> t.x() >> t.y() >> t.z();
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

inline void Vec3::normalize()
{
    float k = 1/sqrt(x()*x() + y()*y() + z()*z());
    v[0] *= k; v[1] *= k; v[2] *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z());
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z());
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x()*v2.x(), v1.y()*v2.y(), v1.z()*v2.z());
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x()/v2.x(), v1.y()/v2.y(), v1.z()/v2.z());
}

inline Vec3 operator*(float t, const Vec3 &v)
{
    return Vec3(v.x()*t, v.y()*t, v.z()*t);
}

inline Vec3 operator/(float t, const Vec3 &v)
{
    return Vec3(v.x()/t, v.y()/t, v.z()/t);
}

inline Vec3 operator*(const Vec3 &v, float t)
{
    return Vec3(v.x()*t, v.y()*t, v.z()*t);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
    return Vec3(v.x()/t, v.y()/t, v.z()/t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2)
{
    return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3((v1.y()*v2.z() - v1.z()*v2.y()),
    (v1.z()*v2.x() - v1.x()*v2.z()),
    (v1.x()*v2.y() - v1.y()*v2.x()));
}

inline Vec3& Vec3::operator+=(const Vec3 &v)
{
    v[0] += v.x();
    v[1] += v.y();
    v[2] += v.z();
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v)
{
    v[0] -= v.x();
    v[1] -= v.y();
    v[2] -= v.z();
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v)
{
    v[0] *= v.x();
    v[1] *= v.y();
    v[2] *= v.z();
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v)
{
    v[0] /= v.x();
    v[1] /= v.y();
    v[2] /= v.z();
    return *this;
}

inline Vec3& Vec3::operator*=(float t)
{
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(float t)
{
    float k = 1/t;
    v[0] *= k;
    v[1] *= k;
    v[2] *= k;
    return *this;
}

inline bool operator==(const Vec3 &v1, const Vec3 &v2)
{
    if (v1.x() != v2.x()) { return false; }
    if (v1.y() != v2.y()) { return false; }
    if (v1.z() != v2.z()) { return false; }
    return true;
}

inline bool operator!=(const Vec3 &v1, const Vec3 &v2)
{
    if (v1.x() == v2.x()) { return false; }
    if (v1.y() == v2.y()) { return false; }
    if (v1.z() == v2.z()) { return false; }
    return true;
}

inline Vec3 unit_vector(Vec3 v)
{
    return v/v.length();
}
