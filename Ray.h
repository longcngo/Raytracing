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
    Vec3 r[3];
    int sign[3];
    float _time;

    Ray() {}
    Ray(const Vec3& o, const Vec3& d, const float t = 0.0f)
    {
        r[0] = o; r[1] = d; r[2] = 1.0f/d; _time = t;
        sign[0] = (r[2].x() < 0);
        sign[1] = (r[2].y() < 0);
        sign[2] = (r[2].z() < 0);
    }
    Vec3 o() const { return r[0]; }
    Vec3 d() const { return r[1]; }
    Vec3 invd() const { return r[2]; }
    float t() const { return _time; }
    Vec3 point_at(float t) const { return r[0] + t * r[1]; }

};
