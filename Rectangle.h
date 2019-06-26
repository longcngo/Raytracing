#ifndef RECTANGLEH
#define RECTANGLEH

#include "Intersection.h"

/*  Rectangle.h

    A class for rectangles in a scene, a subset of parallelograms that are
    axis-aligned i.e. a rectangle that spans the xy-plane at a constant z.

    Using the parallelogram code was unwieldly as the arbitrary vectors are
    harder to use then using simpler, and faster, code for intersections.

*/

class Material;

class Rectangle : public Intersectable
{
public:
    float x_min; float x_max; float y_min; float y_max; float con;
    int const_axis;
    int a0, a1;
    Material *mat_ptr;

    Rectangle() {}
    Rectangle(const float x0, const float x1, const float y0, const float y1, const float k, int c, Material *m)
    {
        x_min = x0; x_max = x1; y_min = y0; y_max = y1; con = k;
        const_axis = c;
        if (c == 0)
        {
            a0 = 1; a1 = 2;
        }
        else if (c == 1)
        {
            a0 = 0; a1 = 2;
        }
        else
        {
            a0 = 0; a1 = 1;
        }
        mat_ptr = m;
    }

    void initXY(const float x0, const float x1, const float y0, const float y1, const float k, Material *m)
    {
        x_min = x0; x_max = x1; y_min = y0; y_max = y1; con = k;
        const_axis = 2;
        a0 = 0; a1 = 1;
        mat_ptr = m;
    }

    void initXZ(const float x0, const float x1, const float z0, const float z1, const float k, Material *m)
    {
        x_min = x0; x_max = x1; y_min = z0; y_max = z1; con = k;
        const_axis = 1;
        a0 = 0; a1 = 2;
        mat_ptr = m;
    }

    void initYZ(const float y0, const float y1 , const float z0, const float z1, const float k, Material *m)
    {
        x_min = y0; x_max = y1; y_min = z0; y_max = z1; con = k;
        const_axis = 0;
        a0 = 1; a1 = 2;
        mat_ptr = m;
    }

    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        float t = (con-r.o()[const_axis])/r.d()[const_axis];

        if (t < t_min || t > t_max)
        {
            return false;
        }

        float x = r.point_at(t)[a0];
        float y = r.point_at(t)[a1];

        if (x < x_min || x > x_max || y < y_min || y > y_max)
        {
            return false;
        }
        else
        {
            isect.t = t;
            isect.p = r.point_at(isect.t);
            isect.normal = Vec3();
            isect.normal[const_axis] += 1.0f;
            isect.uv = Vec2((x-x_min)/(x_max-x_min), (y-y_min)/(y_max-y_min));
            isect.mat = mat_ptr;
            return true;
        }

    }

    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    {
        sample_point = Vec3();
        sample_point[const_axis] = con;
        sample_point[a0] = x_min + xorandf()*(x_max-x_min);
        sample_point[a1] = y_min + xorandf()*(y_max-y_min);
        sample_dir = sample_point-init_point;
        return true;
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        Vec3 small = Vec3();
        small[const_axis] = con;
        small[a0] = x_min;
        small[a1] = y_min;

        Vec3 large = Vec3();
        large[const_axis] = con;
        large[a0] = x_max;
        large[a1] = y_max;

        float epsilon = 0.0001f;
        small[const_axis] -= epsilon; large[const_axis] += epsilon;
        box = bbox(small, large);
        return true;
    }
};

#endif
