#ifndef CUBEH
#define CUBEH

#include "Instance.h"
#include "Rectangle.h"
#include "IntersectList.h"

/*  Cube.h

    A class for cube primitives.

    I chose the implementation based on Shirley's book rather than reusing
    bounding box code, is because of the work needed to find the correct normal
    at the intersection point. It is much easier to reuse code for rectangles
    and have this class essentially be a container class.

*/

class Material;

class Cube : public Intersectable
{
public:
    Vec3 bounds[2];
    IntersectList *rects;
    Material *mat_ptr;

    Cube(){}
    Cube( const Vec3& a, const Vec3& b, Material *m )
    {
        bounds[0] = a; bounds[1] = b; mat_ptr = m;
        Intersectable **list = new Intersectable*[6];
        list[0] = new Rectangle(a.x(), b.x(), a.y(), b.y(), b.z(), 2, mat_ptr);
        list[1] = new Instance(translate(b.x(),0,0)*rotate_y(M_PI), new Rectangle(a.x(), b.x(), a.y(), b.y(), a.z(), 2, mat_ptr));
        list[2] = new Rectangle(a.x(), b.x(), a.z(), b.z(), b.y(), 1, mat_ptr);;
        list[3] = new Instance(translate(b.x(),0,0)*rotate_z(M_PI), new Rectangle(a.x(), b.x(), a.z(), b.z(), a.y(), 1, mat_ptr));
        list[4] = new Rectangle(a.y(), b.y(), a.z(), b.z(), b.x(), 0, mat_ptr);;
        list[5] = new Instance(translate(0,b.y(),0)*rotate_z(M_PI), new Rectangle(a.y(), b.y(), a.z(), b.z(), a.x(), 0, mat_ptr));
        rects = new IntersectList(list, 6);
    }
    Vec3 min() const { return bounds[0]; }
    Vec3 max() const { return bounds[1]; }

    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
    {
        return rects->intersect(r, t_min, t_max, isect);
    }

    virtual bool get_sample_point(const Vec3& init_point, Vec3& sample_point, Vec3& sample_dir) const
    {
        Intersectable *temp_rect = rects->isect_list[int(xorandf()*6)];
        return temp_rect->get_sample_point(init_point, sample_point, sample_dir);
    }

    virtual bool bounding_box(float t0, float t1, bbox& box) const
    {
        box = bbox(min(),max());
        return true;
    }

};


#endif
