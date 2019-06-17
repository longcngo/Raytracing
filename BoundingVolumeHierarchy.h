#ifndef BOUNDINGVOLUMEHIERARCHYH
#define BOUNDINGVOLUMEHIERARCHYH

#include "Intersection.h"

/*  BoundingVolumeHierarchy.h

    A class for a tree structure for bounding boxes. It is an acceleration
    structure that organizes bounding boxes by position in space along a
    random axis.

*/

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

// builds up the BVH tree
BVHNode::BVHNode(Intersectable **l, int n, float time0, float time1)
{
    if (n == 1)
    {
        left = right = l[0];
    }
    else if (n == 2)
    {
        left = l[0];
        right = l[1];
    }
    else
    {
        // choose random axis
        int axis = int(3*xorandf());
        bbox list_box;
        (*l)->bounding_box(time0, time1, list_box);
        // create centroid of the entire list of surfaces at the chosen axis
        float pivot = 0.5f*(list_box.max()-list_box.min())[axis];
        int midpoint = 0;
        bbox box_temp;
        Vec3 centroid;

        // partitons the list based on the surface's centroid in space
        for (int i = 0; i < n; i++)
        {
            l[i]->bounding_box(time0, time1, box_temp);
            centroid =  0.5f*(box_temp.max()-box_temp.min());
            if (centroid[axis] < pivot)
            {
                Intersectable* isect_temp = l[i];
                l[i] = l[midpoint];
                l[midpoint] = isect_temp;
                midpoint++;
            }
        }
        if (midpoint == 0 || midpoint == n) { midpoint = n/2; }

        left = new BVHNode(l, midpoint, time0, time1);
        right = new BVHNode(&l[midpoint], n-midpoint, time0, time1);
    }

    // after being divided, build boxes for the non-leaf nodes
    bbox l_box, r_box;
    if (!left->bounding_box(time0, time1, l_box) || !right->bounding_box(time0, time1, r_box))
    {
        std::cerr << "BVHNode's Bounding Box hasn't been constructed yet" << '\n';
    }
    bb = surrounding_box(l_box, r_box);
}

// checks intersections by recursing down the BVH tree
bool BVHNode::intersect(const Ray& r, float t_min, float t_max, Intersection& isect) const
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

// getter method for the bounding box
bool BVHNode::bounding_box(float t0, float t1, bbox& box) const
{
    box = bb;
    return true;
}

#endif
