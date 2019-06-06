#ifndef MESHH
#define MESHH

#include "Intersection.h"
#include "DynArray.h"

class Material;

class Mesh
{
public:
    DynArray<Vec3> verts;
    DynArray<Vec3> verts_n;
    DynArray<Vec2> verts_uv;
    bool has_n = false;
    bool has_uv = false;
    DynArray<Material*> materials;

    Mesh()
    {
        verts = DynArray<Vec3>(1024);
        verts_n = DynArray<Vec3>(1024);
        verts_uv = DynArray<Vec2>(1024);
        materials = DynArray<Material*>();
    }
    Mesh(Material *m)
    {
        verts = DynArray<Vec3>(1024);
        verts_n = DynArray<Vec3>(1024);
        verts_uv = DynArray<Vec2>(1024);
        materials = DynArray<Material*>();
        materials.append(m);
    }

};

#endif
