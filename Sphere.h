#ifndef SPHEREH
#define SPHEREH

#include "Intersection.h"

/*  Sphere.h

    A class for spheres in a scene.

    The intersect and sample point method uses geometric methods to find the
    result. There is also a seperate class for motion blur due to needing
    two centers.

*/

class Material;

void get_sphere_uv(const Vec3& p, Vec2& uv)
{
    float theta = asin(p.y());
    float phi = atan2(p.z(), p.x());
    uv = Vec2(1-((phi + M_PI)/(2*M_PI)), (0.5f*M_PI+theta)/(M_PI));
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

    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    {
        Vec3 dir_to_center = center-init_point;
        if (dir_to_center.length() < radius) { return false; }
        float dist_to_center_2 = (radius*radius)/(dir_to_center.squared_length());
        float cos_theta_max = sqrt(1-(dist_to_center_2));
        float r0 = xorandf();
        float r1 = xorandf();
        float phi = 2*M_PI*r0;
        float cos_theta = 1 + r1*(cos_theta_max-1);
        float sin_theta = sqrt(1-(cos_theta*cos_theta));
        Vec3 sphere_point = Vec3(cos(phi)*sin_theta, sin(phi)*sin_theta, cos_theta);

        ONB onb;
        onb.initW(dir_to_center);
        Ray to_light = Ray(init_point, onb.local(sphere_point), 0.0f);

        Intersection light_isect;
        if (this->intersect(to_light, 0.0001f, FLT_MAX, light_isect))
        {
            sample_point = light_isect.p;
            sample_dir = unit_vector(sample_point-init_point);
            return true;
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

    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    {
        Vec3 dir_to_center = center(time0+xorandf()*(time1-time0))-init_point;
        if (dir_to_center.length() < radius) { return false; }
        float dist_to_center_2 = (radius*radius)/(dir_to_center.squared_length());
        float cos_theta_max = sqrt(1-(dist_to_center_2));
        float r0 = xorandf();
        float r1 = xorandf();
        float phi = 2*M_PI*r0;
        float cos_theta = 1 + r1*(cos_theta_max-1);
        float sin_theta = sqrt(1-(cos_theta*cos_theta));
        Vec3 sphere_point = Vec3(cos(phi)*sin_theta, sin(phi)*sin_theta, cos_theta);

        ONB onb;
        onb.initW(dir_to_center);
        Ray to_light = Ray(init_point, unit_vector(onb.local(sphere_point)));

        Intersection light_isect;
        if (this->intersect(to_light, 0.0001f, FLT_MAX, light_isect))
        {
            sample_point = light_isect.p;
            sample_dir = unit_vector(sample_point-init_point);
            return true;
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
