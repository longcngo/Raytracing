#pragma once
#ifndef INTERSECTIONH
#define INTERSECTIONH

#include <cfloat>
#include "BoundingBox.h"
#include "Vec2.h"
#include "OrthonormalBasis.h"
#include "RNG.h"

/*  Intersection.h

    A class that represents any surface that can be intersected by a ray,
    including primatives like spheres and triangles, meshes, and volumes. There
    is also a struct to represent data returned from a ray collidng with a
    surface.

    In addition with the intersect function, there is also functions for
    generating a bounding box for acceleration and sample points direct lighting
    calculations from emittable objects.

*/

class Material;

struct Intersection
{
    float t;
    Vec3 p;
    Vec3 normal;
    Vec2 uv;
    Material *mat;
};

class Intersectable
{
public:
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const = 0;
    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    { return false; }
    virtual bool bounding_box(float t0, float t1, bbox& box) const = 0;
};

#endif
