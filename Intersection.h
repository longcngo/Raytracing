#pragma once
#ifndef INTERSECTIONH
#define INTERSECTIONH

#include "BoundingBox.h"

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
    virtual bool bounding_box(float t0, float t1, bbox& box) const = 0;
};

#endif
