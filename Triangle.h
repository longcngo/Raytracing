#ifndef TRIANGLEH
#define TRIANGLEH

#include "Intersection.h"

class Material;

void get_triangle_uv(const Vec3& p, Vec2& uv)
{

}

class Triangle : public Intersectable
{
    Vec3 p0, p1, p2;
    Vec3 n0, n1, n2;
    Material *mat_ptr;

    Triangle() {}
    Triangle(Vec3 a, Vec3 b, Vec3 c, Material *m)
    {
        p0 = a; p1 = b; p2 = c; mat_ptr = m;
        Vec3 e1 = p1-p0; Vec3 e2 = p2-p0;
        Vec3 n = unit_vector(cross(e1,e2));
        Vec3 n0 = n; Vec3 n1 = n; Vec3 n2 = n;
    }
    Triangle(Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 e, Vec3 f, Material *m)
    { p0 = a; p1 = b; p2 = c; n0 = d; n1 = e; n2 = f; mat_ptr = m; }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        float a = p0.x - p1.x;
        float b = p0.y - p1.y;
        float c = p0.z - p1.z;

        float d = p0.x - p2.x;
        float e = p0.y - p2.y;
        float f = p0.z - p2.z;

        float g = r.dir.x;
        float h = r.dir.y;
        float i = r.dir.z;

        float j = p0.x - r.ori.x;
        float k = p0.y - r.ori.y;
        float l = p0.z - r.ori.z;

        float ei_sub_hf = e*i-h*f;
        float gf_sub_di = g*f-d*i;
        float dh_sub_eg = d*h-e*g;

        float denom = a*ei_sub_hf + b*gf_sub_di + c*dh_sub_eg;
        denom = 1/denom;

        float beta = (j*ei_sub_hf + k*gf_sub_di + l*dh_sub_eg)*denom;

        if (beta < 0.0f || beta > 1.0f)
        {
            return false;
        }

        float ak_sub_jb = a*k-j*b;
        float jc_sub_al = j*c-a*l;
        float bl_sub_kc = b*l-k*c;

        float gamma = (i*ak_sub_jb* + h*jc_sub_al + g*bl_sub_kc)*denom;

        if (gamma < 0.0f || gamma + beta > 1.0f)
        {
            return false;
        }

        float t = (f*ak_sub_jb + e*jc_sub_al + d*bl_sub_kc)*denom;

        if (t < t_min || t > t_max)
        {
            return false;
        }
        else
        {
            isect.t = t;
            isect.p = r.point_at(isect.t);
            float alpha = 1 - beta - gamma;
            isect.normal = n0;
            isect.normal *= alpha;
            isect.normal += (n1*beta);
            isect.normal += (n2*gamma);
            isect.normal.normalize();
            Vec2 uv_temp;
            //get_triangle_uv((isect.p-center)/radius, uv_temp)
            isect.uv = uv_temp;
            isect.mat = mat_ptr;
            return true;
        }

    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
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
