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
    float operator[] (int i) const { return e[i]; }
    float& operator[] (int i) { return e[i]; }
    float x() { return e[0]; }
    float y() { return e[1]; }
    const Vec2& operator+() const { return *this; };
    Vec2 operator-() const { return Vec2(-x(), -y()); }

    // binary operators
    inline Vec2& operator+=(const Vec2& v);
    inline Vec2& operator-=(const Vec2& v);
    inline Vec2& operator*=(const Vec2& v);
    inline Vec2& operator/=(const Vec2& v);
    inline Vec2& operator*=(float t);
    inline Vec2& operator/=(float t);

    inline float squared_length() const
    {
        return x()*x() + y()*y();
    }
    inline float length() const
    {
        return sqrt(x()*x() + y()*y());
    }
    inline void normalize();

};

inline std::istream& operator>>(std::istream &is, Vec2 &t)
{
    is >> t.x() >> t.y();
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec2 &t)
{
    os << t.x() << " " << t.y();
    return os;
}

inline void Vec2::normalize()
{
    float k = 1/sqrt(x()*x() + y()*y());
    v[0] *= k; v[1] *= k;
}

inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x()+v2.x(), v1.y()+v2.y());
}

inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x()-v2.x(), v1.y()-v2.y());
}

inline Vec2 operator*(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x()*v2.x(), v1.y()*v2.y());
}

inline Vec2 operator/(const Vec2 &v1, const Vec2 &v2)
{
    return Vec2(v1.x()/v2.x(), v1.y()/v2.y());
}

inline Vec2 operator*(float t, const Vec2 &v)
{
    return Vec2(v.x()*t, v.y()*t);
}

inline Vec2 operator/(float t, const Vec2 &v)
{
    return Vec2(v.x()/t, v.y()/t);
}

inline Vec2 operator*(const Vec2 &v, float t)
{
    return Vec2(v.x()*t, v.y()*t);
}

inline Vec2 operator/(const Vec2 &v, float t)
{
    return Vec2(v.x()/t, v.y()/t);
}

inline float dot(const Vec2 &v1, const Vec2 &v2)
{
    return v1.x()*v2.x() + v1.y()*v2.y();
}

inline Vec2& Vec2::operator+=(const Vec2 &v)
{
    v[0] += v.x();
    v[1] += v.y();
    return *this;
}

inline Vec2& Vec2::operator-=(const Vec2 &v)
{
    v[0] -= v.x();
    v[1] -= v.y();
    return *this;
}

inline Vec2& Vec2::operator*=(const Vec2 &v)
{
    v[0] *= v.x();
    v[1] *= v.y();
    return *this;
}

inline Vec2& Vec2::operator/=(const Vec2 &v)
{
    v[0] /= v.x();
    v[1] /= v.y();
    return *this;
}

inline Vec2& Vec2::operator*=(float t)
{
    v[0] *= t;
    v[1] *= t;
    return *this;
}

inline Vec2& Vec2::operator/=(float t)
{
    float k = 1/t;
    v[0] *= k;
    v[1] *= k;
    return *this;
}

inline bool operator==(const Vec2 &v1, const Vec2 &v2)
{
    if (v1.x() != v2.x()) { return false; }
    if (v1.y() != v2.y()) { return false; }
    return true;
}

inline bool operator!=(const Vec2 &v1, const Vec2 &v2)
{
    if (v1.x() == v2.x()) { return false; }
    if (v1.y() == v2.y()) { return false; }
    return true;
}

inline Vec2 unit_vector(Vec2 v)
{
    return v/v.length();
}
