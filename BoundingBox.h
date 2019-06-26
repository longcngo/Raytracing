#ifndef BOUNDINGBOXH
#define BOUNDINGBOXH

#include "Ray.h"

/*  BoundingBox.h

    A class for boundng boxes, a heurstic for ray-shape intersections by
    creating a box bounded by the smallest and largest points.

    To speed up ray intersections, the intersect function is inlined as the
    functions only handle repetative float evaluations,

*/

inline float ffmin(float a, float b){ return a < b ? a : b; }
inline float ffmax(float a, float b){ return a > b ? a : b; }

class bbox
{
public:
    Vec3 bounds[2];

    bbox(){}
    bbox( const Vec3& a, const Vec3& b ){ bounds[0] = a; bounds[1] = b; }
    Vec3 min() const { return bounds[0]; }
    Vec3 max() const { return bounds[1]; }
    inline bool intersect(const Ray& r, float t_min, float t_max) const;
};

// optimized intersection function based on the paper by Amy Williams et al.
inline bool bbox::intersect(const Ray& r, float t_min, float t_max) const
{
    float interval_min, interval_max, tymin, tymax, tzmin, tzmax;

    // if the sign is negative, the tmin and tmax are implicitly swapped
    // through the sign array
    interval_min = (bounds[r.sign[0]].x()-r.o().x()) * r.invd().x();
    interval_max = (bounds[1-r.sign[0]].x()-r.o().x()) * r.invd().x();

    if (interval_min > interval_max)
    {
        return false;
    }

    tymin = (bounds[r.sign[1]].y()-r.o().y()) * r.invd().y();
    tymax = (bounds[1-r.sign[1]].y()-r.o().y()) * r.invd().y();

    interval_min = ffmin(interval_min, tymin);
    interval_max = ffmax(interval_max, tymax);

    if (interval_min > interval_max)
    {
        return false;
    }

    tzmin = (bounds[r.sign[2]].z()-r.o().z()) * r.invd().z();
    tzmax = (bounds[1-r.sign[2]].z()-r.o().z()) * r.invd().z();

    interval_min = ffmin(interval_min, tzmin);
    interval_max = ffmax(interval_max, tzmax);

    return (interval_min <= interval_max);
}

// generate a bounding box out of two bounding boxes
inline bbox surrounding_box(bbox box0, bbox box1)
{
    Vec3 small = Vec3(ffmin(box0.min().x(), box1.min().x()),
    ffmin(box0.min().y(), box1.min().y()),
    ffmin(box0.min().z(), box1.min().z()));
    Vec3 large = Vec3(ffmax(box0.max().x(), box1.max().x()),
    ffmax(box0.max().y(), box1.max().y()),
    ffmax(box0.max().z(), box1.max().z()));
    return bbox(small, large);
}

#endif
