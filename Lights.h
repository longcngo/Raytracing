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

// class AreaLight : public Light
// {
//   public:
//     Intersectable *shape;
//
//     virtual bool get_light(const Vec3& point, LightSample& ls) const = 0;
// };
//
// class SphereLight : public AreaLight
// {
//
// };

#endif
