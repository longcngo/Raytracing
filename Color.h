#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

/*  Color.h

    A class that represents a color in RGB values. This is a seperate class
    compared to Vec3 as there are different operations between the two. For
    example, clamping or interpolatng is used more for colors than points in
    space.

    Everything being publc and aggressive inlining are used to ensure the class'
    operations are as fast as possible, which is inportant in a CPU intensive
    program like a Raytracer.

*/

class Color
{
public:
    // three elements
    float c[3];

    // constructors
    Color() { c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; };
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
    inline Color operator+(const Color& col) const { return Color(c[0]+col.c[0], c[1]+col.c[1], c[2]+col.c[2]); }
    inline Color operator-(const Color& col) const { return Color(c[0]-col.c[0], c[1]-col.c[1], c[2]-col.c[2]); }
    inline Color operator*(const Color& col) const { return Color(c[0]*col.c[0], c[1]*col.c[1], c[2]*col.c[2]); }
    inline Color operator/(const Color& col) const { return Color(c[0]/col.c[0], c[1]/col.c[1], c[2]/col.c[2]); }
    inline Color operator+(float t) const { return Color(c[0]+t, c[1]+t, c[2]+t); }
    inline Color operator-(float t) const { return Color(c[0]-t, c[1]-t, c[2]-t); }
    inline Color operator*(float t) const { return Color(c[0]*t, c[1]*t, c[2]*t); }
    inline Color operator/(float t) const { return Color(c[0]/t, c[1]/t, c[2]/t); }

    inline Color& operator+=(const Color& col) { *this = *this + col; return *this; }
    inline Color& operator-=(const Color& col) { *this = *this - col; return *this; }
    inline Color& operator*=(const Color& col) { *this = *this * col; return *this; }
    inline Color& operator/=(const Color& col) { *this = *this / col; return *this; }
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

inline Color operator*(float t, const Color &col)
{
    return col*t;
}

inline Color operator*(const Color &col, float t)
{
    return t*col;
}

inline bool operator==(const Color& col1, const Color& col2)
{
    if (col1.c[0] != col2.c[0]) { return false; }
    if (col1.c[1] != col2.c[1]) { return false; }
    if (col1.c[2] != col2.c[2]) { return false; }
    return true;
}
inline bool operator!=(const Color& col1, const Color& col2)
{
    if (col1.c[0] == col2.c[0]) { return false; }
    if (col1.c[1] == col2.c[1]) { return false; }
    if (col1.c[2] == col2.c[2]) { return false; }
    return true;
}

inline Color lerp(const Color& col1, const Color& col2, float t)
{
    return (1.0f-t)*col1 + t*col2;
}
