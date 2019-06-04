#ifndef MESHH
#define MESHH

#include "Intersection.h"

class Material;

class Mesh
{
public:
    Vec3** verts;
    Vec3** vertsN;
    Vec2** vertsUV;
    Material** materials;

    Mesh(){}

}

#endif
