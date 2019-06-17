#ifndef OBJLOADERH
#define OBJLOADERH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mesh.h"
#include "MeshTriangle.h"

/*  ObjLoader.h

    A function that loads up an object file, popullates a mesh and creates mesh
    trangles for the scene.

    C file scanning is used for better performance and cleaner code.

*/

void parse_obj(const char *filename, Mesh* mesh, Intersectable** list, int& list_size)
{
    int verts_cnt = 0;
    int verts_n_cnt = 0;
    int verts_uv_cnt = 0;

    FILE * infile = fopen(filename, "r");
    if (infile == NULL)
    {
        printf("File cannot be opened. Aborting...\n");
        exit(-1);
    }

    char* line = NULL;
    ssize_t read;
    size_t len;

    char line_header[2];
    float x,y,z;
    int p0,p1,p2,n0,n1,n2,uv0,uv1,uv2;

    while ((read = getline(&line, &len, infile)) != -1)
    {
        strncpy(line_header, line, 2);

        if (strcmp(line_header, "v ") == 0)
        {
            sscanf(line, "v %f %f %f",&x,&y,&z);
            mesh->verts.append(Vec3(x,y,z));
        }
        else if (strcmp(line_header, "vt") == 0)
        {
            sscanf(line, "vt %f %f",&x,&y);
            mesh->verts_uv.append(Vec2(x,y));
            mesh->has_uv = true;
        }
        else if (strcmp(line_header, "vn") == 0)
        {
            sscanf(line, "vn %f %f %f",&x,&y,&z);
            mesh->verts_n.append(Vec3(x,y,z));
            mesh->has_n = true;
        }
        else if (strcmp(line_header, "f ") == 0)
        {
            // obj files starts thier indicies with 1 not 0
            // both uv and norm coords
            if (mesh->has_uv && mesh->has_n)
            {
                sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                        &p0, &uv0, &n0, &p1, &uv1, &n1, &p2, &uv2, &n2);
                p0--; p1--; p2--;
                uv0--; uv1--; uv2--;
                n0--; n1--; n2--;
                list[list_size++] = new MeshTriangle(mesh, p0, uv0, n0, p1, uv1, n1, p2, uv2, n2);
            }
            // only uv coords
            else if (mesh->has_uv)
            {
                sscanf(line, "f %i/%i %i/%i %i/%i", &p0, &uv0, &p1, &uv1, &p2, &uv2);
                p0--; p1--; p2--;
                uv0--; uv1--; uv2--;
                list[list_size++] = new MeshTriangle(mesh, p0, uv0, p1, uv1, p2, uv2, true);
            }
            // only norm coords
            else if (mesh->has_n)
            {
                sscanf(line, "f %i//%i %i//%i %i//%i", &p0, &n0, &p1, &n1, &p2, &n2);
                p0--; p1--; p2--;
                n0--; n1--; n2--;
                list[list_size++] = new MeshTriangle(mesh, p0, n0, p1, n1, p2, n2, false);
            }
            // no optional coords
            else
            {
                sscanf(line, "f %i %i %i",&p0,&p1,&p2);
                p0--; p1--; p2--;
                list[list_size++] = new MeshTriangle(mesh, p0, p1, p2);
            }

        }
        else
        {
            continue;
        }

    }

    fclose(infile);

    if (line)
    {
        free(line);
    }

}

#endif
