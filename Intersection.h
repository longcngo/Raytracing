#ifndef INTERSECTIONH
#define INTERSECTIONH

#include "Ray.h"

class Material;

struct Intersection
{
  float t;
  Vec3 p;
  Vec3 normal;
  Material *mat;
};

class Intersectable
{
  public:
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const = 0;
};

#endif
