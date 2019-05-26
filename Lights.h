#ifndef LIGHTH
#define LIGHTH

#include "Shapes.h"

struct LightSample
{
    Vec3 p;
    Vec3 dir;
    Color c;
};

class Light
{
public:
    Color intensity;
    Color light_color;
    virtual bool get_light(const Vec3& point, LightSample& ls) const = 0;
};

class LightList
{
public:
    Light **light_list;
    int list_size;

    LightList(){}
    LightList(Light **l, int n){ light_list = l; list_size = n; }
};

class PointLight : public Light
{
public:
    Vec3 pos;

    PointLight(){}
    PointLight(const Vec3& p, const Color& c, const Color& is){ pos = p; light_color = c; intensity = is; }
    virtual bool get_light(const Vec3& point, LightSample& ls) const
    {
        ls.p = pos;
        ls.dir = ls.p - point;
        ls.c = intensity;
        ls.c *= (1/(ls.dir.squared_length()));
        ls.c *= light_color;
        ls.dir.normalize();
        return true;
    }
};

class SpotLight : public Light
{
public:
    Vec3 from;
    Vec3 to;
    float exponent;
    float cutoff;

    SpotLight(){}
    SpotLight(const Vec3& f, const Vec3& t, const float expo, const float cut, const Color& c, const Color& is)
    { from = f; to = t; exponent = expo; cutoff = cut; light_color = c; intensity = is;}
    virtual bool get_light(const Vec3& point, LightSample& ls) const
    {
        ls.p = from;
        ls.dir = from;
        ls.dir -= point;
        float r2 = ls.dir.squared_length();
        ls.dir.normalize();
        Vec3 spot_dir = unit_vector(from-to);
        float spot_cos_angle = cos(cutoff*(M_PI/360));
        float cos_angle = dot(spot_dir, ls.dir);
        if (cos_angle < spot_cos_angle)
        {
            return false;
        }
        ls.c = intensity;
        ls.c *= (1/(r2*pow(cos_angle, exponent)));
        ls.c *= light_color;
        return true;
    }
};

// class SphereLight : public Light
// {
// public:
//     Sphere *light_sphere;
//
//     SphereLight(){}
//     SphereLight(const Vec3& cen, const float r, const Color& c, const Color& is)
//     { light_sphere = new Sphere(cen, r, new Lambertian(4*c)); light_color = c; intensity = is; }
//     virtual bool get_light(const Vec3& point, LightSample& ls) const
//     {
//         //Intersection isect_sphere;
//         //Ray point_to_sphere = Ray(point, unit_vector(point-(light_sphere->center)), 0.0f);
//         // std::cout << point_to_sphere.o() << '\n';
//         // std::cout << point_to_sphere.d() << '\n';
//         // std::cout << light_sphere->center << '\n';
//         // if (!light_sphere->intersect(point_to_sphere, 0.0001f, FLT_MAX, isect_sphere)) {
//         //     return false;
//         // }
//         Vec3 p;
//         float rad = light_sphere->radius;
//         do {
//           p = 2.0*Vec3(drand48(), drand48(), drand48())-Vec3(rad, rad, rad);
//         } while(p.squared_length() >= rad);
//         ls.p = p;
//         ls.dir = ls.p - point;
//         ls.c = intensity;
//         ls.c *= (1/(ls.dir.squared_length()));
//         ls.c = light_color;
//         ls.dir.normalize();
//         return true;
//     }
// };

// class AreaLight : public Light
// {
//   public:
//     PointLight **point_light_list;
//     Color intensity;
//     AreaLight(){}
//     AreaLight(PointLight **l, const Color& is){ point_light_list = l; intensity = is; }
//
//
// };

#endif
