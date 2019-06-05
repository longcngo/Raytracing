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
    float r() { return c[0]; }
    float b() { return c[1]; }
    float g() { return c[2]; }

    // binary operators w/ and w/o shorthands
    inline Color operator+(const Color& c) const { return Color(r+c.r(), g+c.g(), b+c.b()); }
    inline Color operator-(const Color& c) const { return Color(r-c.r(), g-c.g(), b-c.b()); }
    inline Color operator*(const Color& c) const { return Color(r*c.r(), g*c.g(), b*c.b()); }
    inline Color operator/(const Color& c) const { return Color(r/c.r(), g/c.g(), b/c.b()); }
    inline Color operator+(float t) const { return Color(r+t, g+t, b+t); }
    inline Color operator-(float t) const { return Color(r-t, g-t, b-t); }
    inline Color operator*(float t) const { return Color(r*t, g*t, b*t); }
    inline Color operator/(float t) const { return Color(r/t, g/t, b/t); }

    inline Color& operator+=(const Color& c) { r += c.r(); g += c.g(); b += c.b(); return *this; }
    inline Color& operator-=(const Color& c) { r -= c.r(); g -= c.g(); b -= c.b(); return *this; }
    inline Color& operator*=(const Color& c) { r *= c.r(); g *= c.g(); b *= c.b(); return *this; }
    inline Color& operator/=(const Color& c) { r /= c.r(); g /= c.g(); b /= c.b(); return *this; }
    inline Color& operator+=(float t) { r += t; g += t; b += t; return *this; }
    inline Color& operator-=(float t) { r -= t; g -= t; b -= t; return *this; }
    inline Color& operator*=(float t) { r *= t; g *= t; b *= t; return *this; }
    inline Color& operator/=(float t) { r /= t; g /= t; b /= t; return *this; }

    inline Color& sqrt() { r = pow(r, 0.5f); g = pow(g, 0.5f); b = pow(b, 0.5f); return *this; }
    inline Color& to_int() { r = int(r); g = int(g); b = int(b); return *this; }
    inline Color& clamp()
    {
        if (r < 0.0f) { r = 0.0f; }
        if (g < 0.0f) { g = 0.0f; }
        if (b < 0.0f) { b = 0.0f; }
        if (r > 1.0f) { r = 1.0f; }
        if (g > 1.0f) { g = 1.0f; }
        if (b > 1.0f) { b = 1.0f; }
        return *this;
    }

};

inline std::istream& operator>>(std::istream &is, Color &t)
{
    is >> t.r() >> t.g() >> t.b();
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Color &t)
{
    os << t.r() << " " << t.g() << " " << t.b();
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
    if (c1.r() != c2.r()) { return false; }
    if (c1.g() != c2.g()) { return false; }
    if (c1.b() != c2.b()) { return false; }
    return true;
}
inline bool operator!=(const Color& c1, const Color& c2)
{
    if (c1.r() == c2.r()) { return false; }
    if (c1.g() == c2.g()) { return false; }
    if (c1.b() == c2.b()) { return false; }
    return true;
}

inline Color lerp(const Color& c1, const Color& c2, float t)
{
    return (1.0f-t)*c1 + t*c2;
}
