#ifndef PARALLELOGRAMH
#define PARALLELOGRAMH

#define PARALLEL_EPSILON 0.0000001f

#include "Intersection.h"

class Material;

class Parallelogram : public Intersectable
{
public:
    Vec3 base;
    Vec3 v0, v1;
    Vec3 norm;
    Material *mat_ptr;

    Parallelogram() {}
    Parallelogram(Vec3 a, Vec3 b, Vec3 c, Material *m)
    {
        base = a; v0 = b; v1 = c; mat_ptr = m;
        norm = unit_vector(cross(v0,v1));
    }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        float dot1 = dot(r.d(), norm);

        if (dot1 < PARALLEL_EPSILON && dot1 > PARALLEL_EPSILON)
        {
            return false;
        }

        float dot2 = dot(norm, base);

        float t = (dot2-dot(norm, r.o()))/dot1;

        if (t < t_min || t > t_max)
        {
            return false;
        }

        Vec3 offset = r.point_at(t)-base;

        float u = dot(unit_vector(v0), offset)/v0.length();

        if (u < 0.0f || u > 1.0f)
        {
            return false;
        }

        float v = dot(unit_vector(v1), offset)/v0.length();

        if (v < 0.0f || v > 1.0f)
        {
            return false;
        }

        else
        {
            isect.t = t;
            isect.p = r.point_at(isect.t);
            isect.normal = norm;
            isect.uv = Vec2(u, v);
            isect.mat = mat_ptr;
            return true;
        }

    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        Vec3 p0 = base;
        Vec3 p1 = base + v0;
        Vec3 p2 = base + v1;
        Vec3 p3 = base + v0 + v1;
        Vec3 small = Vec3(ffmin(ffmin(p0.x, p1.x), ffmin(p2.x, p3.x)),
        ffmin(ffmin(p0.y, p1.y), ffmin(p2.y, p3.y)),
        ffmin(ffmin(p0.z, p1.z), ffmin(p2.z, p3.z)));
        Vec3 large = Vec3(ffmax(ffmax(p0.x, p1.x), ffmax(p2.x, p3.x)),
        ffmax(ffmax(p0.y, p1.y), ffmax(p2.y, p3.y)),
        ffmax(ffmax(p0.z, p1.z), ffmax(p2.z, p3.z)));
        box = bbox(small, large);
        return true;
    }

};

#endif
