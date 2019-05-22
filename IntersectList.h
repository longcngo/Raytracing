#ifndef INTERSECTLISTH
#define INTERSECTLISTH

#include "Intersection.h"

/*

Intersect_List:
  A container for every object that a ray can interact i.e. any object extending
  "intersectable".

  The function from "intersectable", loops through every object to get the closest
  object that the ray would collide with, returning true if an object was hit at all

*/

class IntersectList : public Intersectable
{
public:
    IntersectList() {}
    IntersectList(Intersectable **l, int n) { isect_list = l; list_size = n; }
    virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const;
    virtual bool bounding_box(float t0, float t1, bbox& box) const;
    Intersectable **isect_list;
    int list_size;
};

bool IntersectList::intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
{
    Intersection isect_temp;
    bool hit_at_all = false;
    double t_closest = t_max;

    for (int i = 0; i < list_size; i++) {
        if (isect_list[i]->intersect(r, t_min, t_closest, isect_temp)) {
            hit_at_all = true;
            t_closest = isect_temp.t;
            isect = isect_temp;
        }
    }
    return hit_at_all;
}

bool IntersectList::bounding_box(float t0, float t1, bbox& box) const
{
    if (list_size < 1)
    {
        return false;
    }

    bbox temp_box;

    if (!(isect_list[0]->bounding_box(t0, t1, temp_box)))
    {
        return false;
    }
    else
    {
        box = temp_box;
    }

    for (int i = 1; i < list_size; i++)
    {
        if (!(isect_list[i]->bounding_box(t0, t1, temp_box)))
        {
            return false;
        }
        else
        {
            box = surrounding_box(box, temp_box);
        }
    }

    return true;

}

#endif
