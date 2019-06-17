#pragma once
#include "Vec3.h"

/*  Ray.h

    A class that represents a ray with an origin pint and a direction it points
    to. There is also time for motion blur.

    Very straightfoward class. Though, attributes are still public for
    speed up despite having getters. Inversed direction is saved as well as
    booleans for negatives values of inversed direction for efficiency in
    bounding box calculations as rays are reused for other boxes.

*/

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
