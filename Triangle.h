#ifndef TRIANGLEH
#define TRIANGLEH

#define PARALLEL_EPSILON 0.0000001f

#include "Intersection.h"

/*  Triangle.h

    A class for individual triangles in a scene.

    The intersect method uses MT's algorthim which finds barycentric coordinates
    through triple products. For meshes, triangles should have pointers to an
    array of point, normals, and texture coordinates as they are often reused.

*/

class Material;

class Triangle : public Intersectable
{
public:
    Vec3 p0, p1, p2;
    Vec3 n0, n1, n2;
    Vec2 uv0, uv1, uv2;
    Material *mat_ptr;

    Triangle() {}
    Triangle(Vec3 a, Vec3 b, Vec3 c, Material *m)
    {
        p0 = a; p1 = b; p2 = c; mat_ptr = m;
        Vec3 e1 = p1-p0; Vec3 e2 = p2-p0;
        Vec3 n = unit_vector(cross(e1,e2));
        n0 = n; n1 = n; n2 = n;
        uv0 = Vec2(0.0f,0.0f);
        uv1 = Vec2(0.0f,1.0f);
        uv2 = Vec2(1.0f,0.0f);
    }
    Triangle(Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 e, Vec3 f, Material *m)
    {
        p0 = a; p1 = b; p2 = c;
        n0 = d; n1 = e; n2 = f;
        uv0 = Vec2(0.0f,0.0f);
        uv1 = Vec2(0.0f,1.0f);
        uv2 = Vec2(1.0f,0.0f);
        mat_ptr = m;
    }
    Triangle(Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 e, Vec3 f, Vec2 g, Vec2 h, Vec2 i, Material *m)
    {
        p0 = a; p1 = b; p2 = c;
        n0 = d; n1 = e; n2 = f;
        uv0 = g; uv1 = h; uv2 = i;
        mat_ptr = m;
    }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {

        Vec3 e1 = p1-p0; Vec3 e2 = p2-p0;
        Vec3 p = cross(r.d(), e2);
        float denom = dot(p, e1);

        // check if the ray's direction is parallel wth the triangle
        if (fabs(denom) < PARALLEL_EPSILON)
        {
            return false;
        }

        denom = 1/denom;
        Vec3 e0 = r.o()-p0;

        float beta = dot(p, e0)*denom;

        if (beta <= 0.0f || beta >= 1.0f)
        {
            return false;
        }

        Vec3 q = cross(e0,e1);

        float gamma = dot(q, r.d())*denom;

        if (gamma <= 0.0f || gamma + beta >= 1.0f)
        {
            return false;
        }

        float t = dot(q, e2)*denom;

        if (t < t_min || t > t_max)
        {
            return false;
        }
        else
        {
            isect.t = t;
            isect.p = r.point_at(isect.t);
            float alpha = 1 - beta - gamma;
            isect.normal = alpha*n0+beta*n1+gamma*n2;
            isect.normal.normalize();
            isect.uv = alpha*uv0+beta*uv1+gamma*uv2;
            isect.mat = mat_ptr;
            return true;
        }

    }

    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    {
        float r0 = xorandf();
        float r1 = sqrt(xorandf());
        Vec3 q = (1-r0)*p0 + r0*p1;
        sample_point = (1-r1)*q + r1*p2;
        sample_dir = sample_point - init_point;
        return true;
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        Vec3 small = Vec3(ffmin(ffmin(p0.x(), p1.x()), p2.x()),
        ffmin(ffmin(p0.y(), p1.y()), p2.y()),
        ffmin(ffmin(p0.z(), p1.z()), p2.z()));
        Vec3 large = Vec3(ffmax(ffmax(p0.x(), p1.x()), p2.x()),
        ffmax(ffmax(p0.y(), p1.y()), p2.y()),
        ffmax(ffmax(p0.z(), p1.z()), p2.z()));
        box = bbox(small, large);
        return true;
    }

};

#endif
