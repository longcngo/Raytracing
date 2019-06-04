#ifndef MESHTRIANGLEH
#define MESHTRIANGLEH

#define PARALLEL_EPSILON 0.0000001f

#include "Intersection.h"

class Mesh;
class Material;

class MeshTriangle : public Intersectable
{
public:
    Mesh *mesh;
    int p[3];
    int n[3];
    int uv[3];
    bool hasN, hasUV;
    int mat_idx;

    Triangle() {}
    Triangle(Mesh *m, int a, int b, int c, int mat)
    {
        mesh = m;
        p[0] = a; p[1] = b; p[2] = c;
        hasN = false; hasUV = false;
        mat_idx = mat;
    }
    Triangle(Mesh *m, int a, int b, int c, int d, int e, int f, int mat)
    {
        mesh = m;
        p[0] = a; p[1] = b; p[2] = c;
        n[0] = d; n[1] = e; n[2] = f;
        hasN = true; hasUV = false;
        mat_idx = mat;
    }
    Triangle(Mesh *m, int a, int b, int c, int d, int e, int f, int g, int h, int i, int mat)
    {
        mesh = m;
        p[0] = a; p[1] = b; p[2] = c;
        n[0] = d; n[1] = e; n[2] = f;
        uv[0] = g; uv[1] = h; uv[2] = i;
        hasN = true; hasUV = true;
        mat_idx = mat;
    }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {

        Vec3 p0 = mesh->verts[p[0]];
        Vec3 p1 = mesh->verts[p[1]];
        Vec3 p2 = mesh->verts[p[2]];

        Vec3 e1 = p1-p0; Vec3 e2 = p2-p0;
        Vec3 p = cross(r.d(), e2);
        float denom = dot(p, e1);

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
            Vec3 n0, n1, n2;
            Vec2 uv0, uv1, uv2;

            if (hasN)
            {
                n0 = mesh->vertsN[n[0]];
                n1 = mesh->vertsN[n[1]];
                n2 = mesh->vertsN[n[2]];
            }
            else
            {
                Vec3 n = unit_vector(cross(e1,e2));
                n0 = n; n1 = n; n2 = n;
            }

            if (hasUV)
            {
                uv0 = mesh->vertsUV[uv[0]];
                uv1 = mesh->vertsUV[uv[1]];
                uv2 = mesh->vertsUV[uv[2]];
            }
            else
            {
                uv0 = Vec2(0.0f,0.0f);
                uv1 = Vec2(0.0f,1.0f);
                uv2 = Vec2(1.0f,0.0f);
            }

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
        Vec3 p0 = mesh->verts[p[0]];
        Vec3 p1 = mesh->verts[p[1]];
        Vec3 p2 = mesh->verts[p[2]];
        float r0 = xorandf();
        float r1 = sqrt(xorandf());
        Vec3 q = (1-r0)*p0 + r0*p1;
        sample_point = (1-r1)*q + r1*p2;
        sample_dir = sample_point - init_point;
        return true;
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        Vec3 p0 = mesh->verts[p[0]];
        Vec3 p1 = mesh->verts[p[1]];
        Vec3 p2 = mesh->verts[p[2]];
        Vec3 small = Vec3(ffmin(ffmin(p0.x, p1.x), p2.x),
        ffmin(ffmin(p0.y, p1.y), p2.y),
        ffmin(ffmin(p0.z, p1.z), p2.z));
        Vec3 large = Vec3(ffmax(ffmax(p0.x, p1.x), p2.x),
        ffmax(ffmax(p0.y, p1.y), p2.y),
        ffmax(ffmax(p0.z, p1.z), p2.z));
        box = bbox(small, large);
        return true;
    }

};

#endif
