#ifndef BOUNDINGVOLUMEHIERARCHYH
#define BOUNDINGVOLUMEHIERARCHYH

#include "Intersection.h"

class BVHNode : public Intersectable
{
    public:
        bbox bb;
        Intersectable *left;
        Intersectable *right;

        BVHNode(){}
        BVHNode(Intersectable **l, int n, float time0, float time1);
        virtual bool intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const;
        virtual bool bounding_box(float t0, float t1, bbox& box) const;
};

BVHNode::BVHNode(Intersectable **l, int n, float time0, float time1)
{
    if (n == 1)
    {
        left = right = l[0];
        bb = l[0]->bounding_box(t0, t1, bb);
    }
    else if (n == 2)
    {
        left = l[0];
        right = l[1];
        bb = surrounding_box(l[0]->bounding_box(t0, t1, bb), l[1]->bounding_box(t0, t1, bb));
    }
    else
    {
        int axis = int(3*drand48());
        bbox list_box = *l->bounding_box(t0, t1, bb);
        Vec3 midpoint = 0.5f*(l_box.max()-list_box.min());
        Intersectable **l_list = new Intersectable*[n+1];
        Intersectable **r_list = new Intersectable*[n+1];
        int l_idx, r_idx;
        for (int i = 0; i < n; i++)
        {
            if (l[i]->midpoint()[axis] < midpoint[axis])
            {
                l_list[l_idx++] = l[i];
            }
            else
            {
                r_list[r_idx++] = l[i];
            }
        }
        left = new BVHNode(l_list, l_idx, time0, time1);
        right = new BVHNode(r_list, r_idx, time0, time1);
        bbox l_box, r_box;
        if (!left->bounding_box(time0, time1, l_box) || !right->bounding_box(time0, time1, r_box))
        {
            std::cerr << "BVHNode's Bounding Box hasn't been constructed yet" << '\n';
        }
        bb = surrounding_box(left->bounding_box(), right->bounding_box());

    }
}

bool BVHNode::intersect(const Ray& r, float t_min, float t_max, Intersection& isect)
{
    if (bb.intersect(r, t_min, t_max))
    {
        Intersection r_isect, l_isect;
        bool left_hit = left->intersect(r, t_min, t_max, l_isect);
        bool right_hit = right->intersect(r, t_min, t_max, r_isect);

        if (left_hit && right_hit)
        {
            if (l_isect.t < r_isect.t)
            {
                isect = l_isect;
            }
            else
            {
                isect = r_isect;
            }
            return true;
        }
        else if (left_hit)
        {
            isect = l_isect;
            return true;
        }
        else if (right_hit)
        {
            isect = r_isect;
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

bbox BVHNode::bounding_box(float t0, float t1, bbox& box)
{
    bb = box;
    return true;
}

#endif
