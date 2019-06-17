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
    Vec3 _min;
    Vec3 _max;

    bbox(){}
    bbox( const Vec3& a, const Vec3& b ){ _min = a; _max = b; }
    Vec3 min() const { return _min; }
    Vec3 max() const { return _max; }
    inline bool intersect(const Ray& r, float t_min, float t_max) const;
};

// optimized intersection function based on the paper by Amy Williams et al.
inline bool bbox::intersect(const Ray& r, float t_min, float t_max) const
{
    for (int a = 0; a < 3; a++) {
        float inv_dir = 1/r.d()[a];
        float t0 = (min()[a]-r.o()[a]) * (inv_dir);
        float t1 = (max()[a]-r.o()[a]) * (inv_dir);
        if (inv_dir < 0)
        {
            std::swap(t0, t1);
        }
        t_min = t0 < t_min ? t_min : t0;
        t_max = t1 > t_max ? t_max : t1;
        if (t_max < t_min)
        {
            return false;
        }
    }

    return true;

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
