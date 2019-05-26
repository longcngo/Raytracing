#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

class Color
{
public:
    // three elements
    float r;
    float g;
    float b;

    // constructors
    Color() { r = 0.0f; g = 0.0f; b = 0.0f; };
    Color(const float rr, const float gg, const float bb)
    {
        r = rr;
        g = gg;
        b = bb;
    };

    // unary operatooers
    float operator[] (int i) const
    {
        switch (i) {
            case 0:
            return r;
            case 1:
            return g;
            case 2:
            return b;
            default:
            throw std::invalid_argument( "out of bounds value" );
        }
    }
    float& operator[] (int i)
    {
        switch (i) {
            case 0:
            return r;
            case 1:
            return g;
            case 2:
            return b;
            default:
            throw std::invalid_argument( "out of bounds value" );
        }
    }

    // binary operators w/ and w/o shorthands
    inline Color operator+(const Color& c) const { return Color(r+c.r, g+c.g, b+c.b); }
    inline Color operator-(const Color& c) const { return Color(r-c.r, g-c.g, b-c.b); }
    inline Color operator*(const Color& c) const { return Color(r*c.r, g*c.g, b*c.b); }
    inline Color operator/(const Color& c) const { return Color(r/c.r, g/c.g, b/c.b); }
    inline Color operator+(float t) const { return Color(r+t, g+t, b+t); }
    inline Color operator-(float t) const { return Color(r-t, g-t, b-t); }
    inline Color operator*(float t) const { return Color(r*t, g*t, b*t); }
    inline Color operator/(float t) const { return Color(r/t, g/t, b/t); }

    inline Color& operator+=(const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
    inline Color& operator-=(const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
    inline Color& operator*=(const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
    inline Color& operator/=(const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }
    inline Color& operator+=(float t) { r += t; g += t; b += t; return *this; }
    inline Color& operator-=(float t) { r -= t; g -= t; b -= t; return *this; }
    inline Color& operator*=(float t) { r *= t; g *= t; b *= t; return *this; }
    inline Color& operator/=(float t) { r /= t; g /= t; b /= t; return *this; }

    inline Color& sqrt() { r = pow(r, 0.5f); g = pow(g, 0.5f); b = pow(b, 0.5f); return *this; }
    inline Color& to_int() { r = int(r); g = int(g); b = int(b); return *this; }

    inline void clamp();

};

inline std::istream& operator>>(std::istream &is, Color &t)
{
    is >> t.r >> t.g >> t.b;
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Color &t)
{
    os << t.r << " " << t.g << " " << t.b;
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

inline void Color::clamp()
{
    if (r < 0.0f) { r = 0.0f; }
    if (g < 0.0f) { g = 0.0f; }
    if (b < 0.0f) { b = 0.0f; }
    if (r > 1.0f) { r = 1.0f; }
    if (g > 1.0f) { g = 1.0f; }
    if (b > 1.0f) { b = 1.0f; }
}
