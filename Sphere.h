#ifndef SPHEREH
#define SPHEREH

#include "Intersection.h"

class Material;

void get_sphere_uv(const Vec3& p, Vec2& uv)
{
    float theta = asin(p.y);
    float phi = atan2(p.z, p.x);
    uv.x = 1-((phi + M_PI)/(2*M_PI));
    uv.y = (0.5f*M_PI+theta)/(M_PI);
}

class Sphere : public Intersectable
{
public:
    Vec3 center;
    float radius;
    Material *mat_ptr;

    Sphere() {}
    Sphere(Vec3 cen, float r, Material *m) { center = cen; radius = r; mat_ptr = m;}
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        Vec3 oc = r.o() - center;
        float a = dot(r.d(), r.d());
        float b = 2.0*dot(oc, r.d());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b*b - 4*a*c;
        if (discriminant > 0)
        {
            float t_temp = (-b - sqrt(discriminant)) / (2.0f*a);
            if (t_max < t_temp || t_temp < t_min)
            {
                t_temp = (-b + sqrt(discriminant)) / (2.0f*a);
            }

            if (t_max < t_temp || t_temp < t_min)
            {
                return false;
            }
            else
            {
                isect.t = t_temp;
                isect.p = r.point_at(isect.t);
                isect.normal = (isect.p - center);
                isect.normal.normalize();
                Vec2 uv_temp;
                get_sphere_uv((isect.p-center)/radius, uv_temp);
                isect.uv = uv_temp;
                isect.mat = mat_ptr;
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        box = bbox(center - Vec3(radius, radius, radius), center + Vec3(radius, radius, radius));
        return true;
    }



};

class MovingSphere : public Intersectable
{
public:
    Vec3 center0, center1;
    float time0, time1;
    float radius;
    Material *mat_ptr;

    MovingSphere() {}
    MovingSphere(Vec3 cen0, Vec3 cen1, float t0, float t1, float r, Material *m)
    { center0 = cen0; center1 = cen1; time0 = t0; time1 = t1; radius = r; mat_ptr = m;}
    Vec3 center(float t) const
    {
        //std::cout << center0 + ((t-time0)/(time1-time0))*(center1-center0) << '\n';
        return center0 + ((t-time0)/(time1-time0))*(center1-center0);
    }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        Vec3 oc = r.o() - center(r.t());
        float a = dot(r.d(), r.d());
        float b = 2.0*dot(oc, r.d());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b*b - 4*a*c;
        if (discriminant > 0)
        {
            float t_temp = (-b - sqrt(discriminant)) / (2.0f*a);
            if (t_max < t_temp || t_temp < t_min)
            {
                t_temp = (-b + sqrt(discriminant)) / (2.0f*a);
            }

            if (t_max < t_temp || t_temp < t_min)
            {
                return false;
            }
            else
            {
                // std::cout << center0 << '\n';
                // std::cout << center1 << '\n';
                // std::cout << time0 << '\n';
                // std::cout << time1 << '\n';
                // std::cout << r.t() << '\n';
                // std::cout << center(r.t()) << '\n' << '\n';
                isect.t = t_temp;
                isect.p = r.point_at(isect.t);
                Vec3 cen = center(r.t());
                isect.normal = (isect.p - cen);
                isect.normal.normalize();
                Vec2 uv_temp;
                get_sphere_uv((isect.p-cen)/radius, uv_temp);
                isect.uv = uv_temp;
                isect.mat = mat_ptr;
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        bbox box0 = bbox(center0 - Vec3(radius, radius, radius), center0 + Vec3(radius, radius, radius));
        bbox box1 = bbox(center1 - Vec3(radius, radius, radius), center1 + Vec3(radius, radius, radius));
        box = surrounding_box(box0, box1);
        return true;
    }

};

#endif
