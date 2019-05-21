#pragma once
#include "Vec3.h"

class Ray
{
public:
    Vec3 ori;
    Vec3 dir;
    float _time;

    Ray() {}
    Ray(const Vec3& o, const Vec3& d, const float t = 0.0f)
    { ori = o; dir = d; _time = t; }
    Vec3 o() const { return ori; }
    Vec3 d() const { return dir; }
    float t() const { return _time; }
    Vec3 point_at(float t) const { return ori + t * dir; }
};
