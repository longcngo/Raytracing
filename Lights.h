#ifndef LIGHTH
#define LIGHTH

#include "Vec3.h"
#include "Color.h"

struct LightSample
{
  Vec3 p;
  Vec3 dir;
  Color inten;
};

class light
{
  public:
    virtual bool get_light(const Vec3& point, LightSample& ls) const;
};

class PointLight : public Light
{
  public:
    vec3 pos;
    color intensity;

    PointLight(){}
    PointLight(const Vec3& p, const color& is){ pos = p; intensity = is; }
    virtual bool get_light(const Vec3& point, LightSample& ls) const
    {
      ls.p = pos;
      ls.dir -= point;
      ls.inten = intensity;
      ls.inten *= (1/(ls.dir.squared_length()))
      ls.dir.normalize();
      return true;
    }
};

class SpotLight : public Light
{
  public:
    Vec3 from;
    Vec3 to;
    Color intensity;
    float exponent;
    float cutoff;

    SpotLight(){}
    SpotLight(const Vec3& f, const Vec& t, const float expo, const float cut)
    { from = f; to = t; exponent = expo; cutoff = cut; }
    virtual void get_light(const Vec3& point, LightSample& ls) const
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
      ls.inten = intensity;
      ls.inten *= (1/(r2*pow(cos_angle, exponent)));
      return true
    }
};

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
