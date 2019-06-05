#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Color
{
public:
    // three elements
    float c[3];

    // constructors
    Color() { c[0] = c[1] = c[2] = 0; };
    Color(const float rr, const float gg, const float bb)
    {
        c[0] = rr;
        c[1] = gg;
        c[2] = bb;
    };

    // unary operatooers

    float operator[] (int i) const { return c[i]; }
    float& operator[] (int i) { return c[i]; }
    float r() const { return c[0]; }
    float b() const { return c[1]; }
    float g() const { return c[2]; }

    // binary operators w/ and w/o shorthands
    inline Color operator+(const Color& c) const { return Color(c[0]+c.c[0], c[1]+c.c[1], c[2]+c.c[2]); }
    inline Color operator-(const Color& c) const { return Color(c[0]-c.c[0], c[1]-c.c[1], c[2]-c.c[2]); }
    inline Color operator*(const Color& c) const { return Color(c[0]*c.c[0], c[1]*c.c[1], c[2]*c.c[2]); }
    inline Color operator/(const Color& c) const { return Color(c[0]/c.c[0], c[1]/c.c[1], c[2]/c.c[2]); }
    inline Color operator+(float t) const { return Color(c[0]+t, c[1]+t, c[2]+t); }
    inline Color operator-(float t) const { return Color(c[0]-t, c[1]-t, c[2]-t); }
    inline Color operator*(float t) const { return Color(c[0]*t, c[1]*t, c[2]*t); }
    inline Color operator/(float t) const { return Color(c[0]/t, c[1]/t, c[2]/t); }

    inline Color& operator+=(const Color& c) { *this = *this + c; return *this; }
    inline Color& operator-=(const Color& c) { *this = *this - c; return *this; }
    inline Color& operator*=(const Color& c) { *this = *this * c; return *this; }
    inline Color& operator/=(const Color& c) { *this = *this / c; return *this; }
    inline Color& operator+=(float t) { c[0] += t; c[1] += t; c[2] += t; return *this; }
    inline Color& operator-=(float t) { c[0] -= t; c[1] -= t; c[2] -= t; return *this; }
    inline Color& operator*=(float t) { c[0] *= t; c[1] *= t; c[2] *= t; return *this; }
    inline Color& operator/=(float t) { c[0] /= t; c[1] /= t; c[2] /= t; return *this; }

    inline Color& sqrt() { c[0] = pow(c[0], 0.5f); c[1] = pow(c[1], 0.5f); c[2] = pow(c[2], 0.5f); return *this; }
    inline Color& to_int() { c[0] = int(c[0]); c[1] = int(c[1]); c[2] = int(c[2]); return *this; }
    inline Color& clamp()
    {
        if (c[0] < 0.0f) { c[0] = 0.0f; }
        if (c[1] < 0.0f) { c[1] = 0.0f; }
        if (c[2] < 0.0f) { c[2] = 0.0f; }
        if (c[0] > 1.0f) { c[0] = 1.0f; }
        if (c[1] > 1.0f) { c[1] = 1.0f; }
        if (c[2] > 1.0f) { c[2] = 1.0f; }
        return *this;
    }

};

inline std::istream& operator>>(std::istream &is, Color &t)
{
    is >> t.c[0] >> t.c[1] >> t.c[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Color &t)
{
    os << t.c[0] << " " << t.c[1] << " " << t.c[2];
    return os;
}

inline Color operator*(float t, const Color &c)
{
    return c*t;
}

inline Color operator*(const Color &c, float t)
{
    return t*c;
}

inline bool operator==(const Color& c1, const Color& c2)
{
    if (c1.c[0] != c2.c[0]) { return false; }
    if (c1.c[1] != c2.c[1]) { return false; }
    if (c1.c[2] != c2.c[2]) { return false; }
    return true;
}
inline bool operator!=(const Color& c1, const Color& c2)
{
    if (c1.c[0] == c2.c[0]) { return false; }
    if (c1.c[1] == c2.c[1]) { return false; }
    if (c1.c[2] == c2.c[2]) { return false; }
    return true;
}

inline Color lerp(const Color& c1, const Color& c2, float t)
{
    return (1.0f-t)*c1 + t*c2;
}
