#ifndef INSTANCEH
#define INSTANCEH

#include "Matrix.h"
#include "Intersection.h"

/*  Instance.h

    A wrapper class for transformatons of surfaces.

    The class is for any arbitrary transformaton, hence the usage for matrices
    than creatng seperate classes for simple transformations. The implementation
    is rudamentary due to how elegantly simple instancing is. The bounding box
    derivation is based on James Arvo's algorithm as the minimum and maximum
    should be checked for each part of the dot product than the dot product
    itself returned from the transform functions.

*/

class Instance : public Intersectable
{
public:
    Intersectable *shape;
    Matrix transform;
    Matrix transform_inverse;

    Instance(){}
    Instance(Matrix t, Intersectable *s)
    {
        transform = t;
        shape = s;
        transform_inverse = t.inverse();
    }
    Instance(Matrix t, Matrix i, Intersectable *s)
    {
        transform = t;
        shape = s;
        transform_inverse = i;
    }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        Vec3 trans_ori = loc_transform(transform_inverse, r.o());
        Vec3 trans_dir = vec_transform(transform_inverse, r.d());
        Ray trans_ray = Ray(trans_ori, trans_dir, r.t());

        if (shape->intersect(trans_ray, t_min, t_max, isect))
        {
            isect.p = loc_transform(transform, rec.p);
            isect.normal = vec_transform(transform_inverse.transpose_mat(), rec.n);
        }
        else
        {
            return false;
        }

    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        Vec3 translate = Vec3(transform[3][0], transform[3][1], transform[3][2]);
        Vec3 trans_min, trans_max = translate;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                float a = transform[i][j]*box.min()[j];
                float b = transform[i][j]*box.max()[j];
                trans_min[i] += ffmin(a,b);
                trans_max[i] += ffmax(a,b);
            }
        }

        box = bbox(trans_min, trans_max);
        return true;
    }

};

#endf
