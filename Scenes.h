#ifndef SCENESH
#define SCENESH
#define STB_IMAGE_IMPLEMENTATION

#include <cfloat>
#include "stb_image.h"
#include "DynArray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Rectangle.h"
#include "Cube.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "Material.h"
#include "Instance.h"
#include "IntersectList.h"
#include "BoundingVolumeHierarchy.h"
#include "Lights.h"

/*  Scenes.h

    A collections of pregenerated scenes for testing purposes

*/

// sphere and point light test scene
Intersectable *simple_sphere_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));

    return new IntersectList(list, 2);
}

// triangle test scene
Intersectable *simple_triangle_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.15f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Triangle(Vec3(0.25f, 0.0f, -0.25f), Vec3(-1.25f, 0.0f, 1.25f),
                           Vec3(0.0f,1.25f,0.0f), new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));

    return new IntersectList(list, 2);
}

// parallelogram test scene
Intersectable *simple_rect_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[2];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    Parallelogram *para = new Parallelogram(Vec3(-0.25f, 0.0f, 0.25f), Vec3(0.0f,1.0f,1.25f), Vec3(-1.25f,0.0f,0.0f),
                                new DiffuseEmitter(new ConstantTexture(Color(4.0f,4.0f,4.0f))));
    l_list[1] = new AreaLight(para, Color(4.0f,4.0f,4.0f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 2);

    int list_size = 2;
    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = para;

    return new IntersectList(list, list_size);
}

// cube primatives test scene
Intersectable *simple_cube_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    int list_size = 2;
    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Instance(rotate_y(M_PI), new Cube(Vec3(0.00f, 0.0f, 0.00f),Vec3(1.00f, 1.50f, 1.00f), new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f)))));

    return new IntersectList(list, list_size);
}

// cube mesh test scene
Intersectable *simple_mesh_scene1(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    int list_size = 1;
    Intersectable **list = new Intersectable*[5000];
    list[0] = new Sphere(Vec3(0.0f,-1001.0f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    Texture *turb_stripe = new TurbStripeTexture(1.0f, 5.0f, 10.0f);
    Mesh *cube_mesh = new Mesh(new Lambertian(turb_stripe));
    parse_obj("input/objs/cube.obj", cube_mesh, list, list_size);

    return new BVHNode(list, list_size, 0.0f, 0.0f);
}

// cow mesh test scene
Intersectable *simple_mesh_scene2(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(4.0f, 2.5f, 4.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    int list_size = 1;
    Intersectable **list = new Intersectable*[5000];
    list[0] = new Sphere(Vec3(0.0f,-1001.0f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    Mesh *cow_mesh = new Mesh(new Lambertian(new ConstantTexture(Color(0.9f, 1.0f, 0.9f))));
    parse_obj("input/objs/cow.obj", cow_mesh, list, list_size);

    return new BVHNode(list, list_size, 0.0f, 0.0f);
}

// instancing test scene
Intersectable *simple_transform_scene1(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    Sphere *sp  = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));
    list[1] = new Instance(rotate_y(0.5*M_PI)*scale(2.0f, 1.0f, 2.0f)*translate(0.5f,0.5f,0.5f), sp);

    return new IntersectList(list, 2);
}

// stripe texture test scene
Intersectable *simple_texture_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    Texture *stripes = new StripeTexture(new ConstantTexture(Color(0.5f,0.5f,0.5f)), new ConstantTexture(Color(0.9f, 0.9f, 0.9f)), 0.3f);
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(stripes));
    list[1] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));

    return new IntersectList(list, 2);
}

// perlin noise texture test scene
Intersectable *simple_perlin_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    Texture *pertext = new NoiseTexture(2.0f);
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(pertext));
    list[1] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(pertext));

    return new IntersectList(list, 2);
}

// turbulance texture test scene
Intersectable *simple_turb_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[4];
    Texture *pertext = new NoiseTexture(5.0f);
    Texture *turb = new TurbTexture(5.0f);
    Texture *turb_stripe = new TurbStripeTexture(1.0f, 5.0f, 10.0f);
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(turb_stripe));
    list[1] = new Sphere(Vec3(-1.25f, 0.0f, 1.25f), 1.25f, new Lambertian(turb_stripe));
    list[2] = new Sphere(Vec3(1.25f,0.0f,-1.25f), 1.25f, new Lambertian(turb));
    list[3] = new Sphere(Vec3(-1.25f, 0.0f, -1.25f), 1.25f, new Lambertian(pertext));

    return new IntersectList(list, 4);
}

// image texture test scene using a grid texture
Intersectable *simple_img_test_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(5.0f, 4.0f, 5.0f);
    Vec3 lookat = Vec3(0.0f,1.0f,0.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("input/textures/colorgrid.png", &nx, &ny, &nn, 0);
    Material *earth_mat = new Lambertian(new ImageTexture(tex_data, nx, ny));
    list[0] = new Sphere(Vec3(0.0f,-1000.0f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Sphere(Vec3(0.0f,1.0f,0.0f), 1.0f, earth_mat);

    return new IntersectList(list, 2);
}

// image texture test scene using an earth texture
Intersectable *simple_earth_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(5.0f, 4.0f, 5.0f);
    Vec3 lookat = Vec3(0.0f,1.0f,0.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    //l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 0);

    Intersectable **list = new Intersectable*[1];
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("input/textures/earthmap.jpg", &nx, &ny, &nn, 0);
    Material *earth_mat = new Lambertian(new ImageTexture(tex_data, nx, ny));
    list[0] = new Sphere(Vec3(0.0f,1.0f,0.0f), 1.0f, earth_mat);

    return new IntersectList(list, 1);
}

// spotlight test scene
Intersectable *simple_spotlight_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new SpotLight(Vec3(10.0f, 10.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[2];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));

    return new IntersectList(list, 2);
}

// specular test scene
Intersectable *simple_mirror_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(0.25f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[3];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Sphere(Vec3(-1.25f, 0.0f, 1.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));
    list[2] = new Sphere(Vec3(1.25f,0.0f,-1.25f), 1.25f, new Metal(new ConstantTexture(Color(0.8f,0.6f,0.2f)), 0.3f));
    return new IntersectList(list, 3);
}

// glass test scene
Intersectable *simple_glass_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(0.25f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[3];
    list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[1] = new Sphere(Vec3(-1.25f, 0.0f, 1.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f, 0.2f, 0.2f))));
    list[2] = new Sphere(Vec3(1.25f,0.0f,-1.25f), 1.25f, new Dielectric(1.5f));
    return new IntersectList(list, 3);
}

// emittable sphere test
Intersectable *simple_emitter_scene1(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 6.0f, 9.0f);
    Vec3 lookat = Vec3(0.25f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    Sphere *spl = new Sphere(Vec3(-2.25f, 5.0f, 2.25f), 1.25f, new DiffuseEmitter(new ConstantTexture(Color(1.0f,1.0f,1.0f))));
    l_list[0] = new AreaLight(spl, Color(1.0f,1.0f,1.0f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    Intersectable **list = new Intersectable*[3];
    list[0] = spl;
    list[1] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[2] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f,0.2f,0.2f))));
    return new IntersectList(list, 3);
}

// emittable objects test
Intersectable *simple_emitter_scene2(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
    Vec3 lookat = Vec3(0.25f,0.0f,0.5f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Intersectable **list = new Intersectable*[4];
    Parallelogram *para0 = new Parallelogram(Vec3(1.25f, 0.0f, -1.25f), Vec3(0.0f,1.0f,1.25f), Vec3(-1.25f,0.0f,0.0f),
                                new DiffuseEmitter(new ConstantTexture(Color(1.0f,1.0f,1.0f))));
    Parallelogram *para1 = new Parallelogram(Vec3(-2.50f, 1.0f, 2.50f), Vec3(-1.25f,1.0f,2.50f), Vec3(-2.5f,1.0f,1.25f),
                                new DiffuseEmitter(new ConstantTexture(Color(1.0f,1.0f,1.0f))));
    list[0] = para0;
    list[1] = para1;
    list[2] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(new ConstantTexture(Color(0.5f,0.5f,0.5f))));
    list[3] = new Sphere(Vec3(-1.25f, 0.0f, 1.25f), 1.25f, new Lambertian(new ConstantTexture(Color(1.0f,0.2f,0.2f))));

    Light ** l_list = new Light*[2];
    l_list[0] = new AreaLight(para0, Color(1.0f,1.0f,1.0f), Color(100.0f, 98.0f, 88.0f));
    l_list[1] = new AreaLight(para1, Color(1.0f,1.0f,1.0f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 2);

    return new IntersectList(list, 4);
}

// looking between two sphere
Intersectable *two_sphere_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(0.0f, 0.0f, -1.0f);
    Vec3 lookat = Vec3(0.0f,0.0f,-1.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 90.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 0);

    Intersectable *list[2];
    float R = cos(M_PI/4);
    list[0] = new Sphere(Vec3(-R,0.0f,-1.0f), R, new Lambertian(new ConstantTexture(Color(1.0f,0.2f,0.0f))));
    list[1] = new Sphere(Vec3(R,0.0f,-1.0f), R, new Lambertian(new ConstantTexture(Color(0.0f,0.2f,1.0f))));
    return new IntersectList(list, 2);
}

// three spheres in a line
Intersectable *three_sphere_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(-2.0f, 2.0f, 1.0f);
    Vec3 lookat = Vec3(0.0f,0.0f,-1.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 10.0f, 5.0f), Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 0);

    Intersectable *list[5];
    list[0] = new Sphere(Vec3(0.0f,0.0f,-1.0f), 0.5f, new Lambertian(new ConstantTexture(Color(0.1f,0.2f,0.5f))));
    list[1] = new Sphere(Vec3(0.0f,-100.5f,-1.0f), 100.0f, new Lambertian(new ConstantTexture(Color(0.8f,0.8f,0.0f))));
    list[2] = new Sphere(Vec3(1.0f,0.0f,-1.0f), 0.5f, new Metal(new ConstantTexture(Color(0.8f,0.6f,0.2f)), 0.3f));
    list[3] = new Sphere(Vec3(-1.0f,0.0f,-1.0f), 0.5f, new Dielectric(1.5f));
    list[4] = new Sphere(Vec3(-1.0f,0.0f,-1.0f), -0.45f, new Dielectric(1.5f));
    return new BVHNode(list, 5, 0.0f, 0.0f);
}

// random sphere scene from "Ray Tracing in a Weekend"
Intersectable *random_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(13.0f, 2.0f, 3.0f);
    Vec3 lookat = Vec3(0.0f,0.0f,0.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.1f;
    float t0 = 0;
    float t1 = 1;
    cam = Camera(lookfrom, lookat, vup, 20.0f, float(x_max)/float(y_max), aperature, dist_to_focus, t0, t1);

    Light ** l_list = new Light*[1];
    l_list[0] = new PointLight(Vec3(10.0f, 20.0f, 10.0f), Color(1.0f, 0.9f, 0.8f), Color(10.0f, 9.0f, 8.0f));
    lights = LightList(l_list , 1);

    int n = 50000;
    Intersectable **list = new Intersectable*[n+1];
    Texture *checker = new CheckerTexture(new ConstantTexture(Color(0.2f, 0.3f, 0.1f)), new ConstantTexture(Color(0.9f, 0.9f, 0.9f)));
    list[0] = new Sphere(Vec3(0.0f,-1000.0f, 0.0f), 1000.0f, new Lambertian(checker));
    int i = 1;
    Material *sphere_mat_ptr;

    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {

            float choose_mat = xorandf();
            Vec3 cen = Vec3(a+0.9f*xorandf(),0.2f,b+0.9f*xorandf());
            if ((cen-Vec3(4.0f,0.2f,0.0f)).length() > 0.9) {
                if (choose_mat < 0.8) // diffuse
                {
                    sphere_mat_ptr = new Lambertian(new ConstantTexture(Color(xorandf()*xorandf(), xorandf()*xorandf(), xorandf()*xorandf())));
                    list[i++] = new MovingSphere(cen, (cen+Vec3(0.0f, 0.5f*xorandf(), 0.0f)), 0, 1, 0.2f, sphere_mat_ptr);
                }
                else if (choose_mat < 0.95) //metal
                {
                    sphere_mat_ptr = new Metal(new ConstantTexture(Color(0.5f*(1+xorandf()), 0.5f*(1+xorandf()), 0.5f*(1+xorandf()))), 0.5*xorandf());
                    list[i++] = new Sphere(cen, 0.2f, sphere_mat_ptr);
                }
                else // glass
                {
                    sphere_mat_ptr = new Dielectric(1.5f);
                    list[i++] = new Sphere(cen, 0.2f, sphere_mat_ptr);
                }
            }

        }
    }

    list[i++] = new Sphere(Vec3(-4.0f,1.0f,0.0f), 1.0f, new Lambertian(new ConstantTexture(Color(0.4f,0.2f,0.1f))));
    list[i++] = new Sphere(Vec3(0.0f,1.0f,0.0f), 1.0f, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(4.0f,1.0f,0.0f), 1.0f, new Metal(new ConstantTexture(Color(0.7f,0.6f,0.5f)), 0.0f));

    return new BVHNode(list, i, t0, t1);
}

Intersectable *cornell_box_blank_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(278.0f, 278.0f, -800.0f);
    Vec3 lookat = Vec3(278.0f, 278.0f, 0.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.0f;
    float vfov = 40.0;
    cam = Camera(lookfrom, lookat, vup, vfov, float(x_max)/float(y_max), aperature, dist_to_focus, 0.0f, 1.0f);

    Material *red = new Lambertian(new ConstantTexture(Color(0.65f, 0.05f, 0.05f)));
    Material *green = new Lambertian(new ConstantTexture(Color(0.12f, 0.45f, 0.15f)));
    Material *white = new Lambertian(new ConstantTexture(Color(0.73f, 0.73f, 0.73f)));
    Material *light = new DiffuseEmitter(new ConstantTexture(Color(15.0f, 15.0f, 15.0f)));

    Intersectable **list = new Intersectable*[10];
    Instance *light_rect = new Instance(translate(213,554,0)*rotate_z(M_PI), new Rectangle(213.0f, 343.0f, 227.0f, 332.0f, 554.0f, 1, light));
    list[0] = light_rect;
    list[1] = new Instance(translate(555,0,555)*rotate_y(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 0, red));
    list[2] = new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 0, green);
    list[3] = new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 1, white);
    list[4] = new Instance(translate(555,555,0)*rotate_z(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 1, white));
    list[5] = new Instance(translate(555,0,555)*rotate_y(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 2, white));

    Light ** l_list = new Light*[1];
    l_list[0] = new AreaLight(light_rect, Color(15.0f, 15.0f, 15.0f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 0);

    return new BVHNode(list, 6, 0.0f, 0.0f);
}

Intersectable *cornell_box_cubes_scene(Camera& cam, LightList& lights, float x_max, float y_max)
{
    Vec3 lookfrom = Vec3(278.0f, 278.0f, -800.0f);
    Vec3 lookat = Vec3(278.0f, 278.0f, 0.0f);
    Vec3 vup = Vec3(0.0f,1.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperature = 0.0f;
    float vfov = 40.0;
    cam = Camera(lookfrom, lookat, vup, vfov, float(x_max)/float(y_max), aperature, dist_to_focus, 0.0f, 1.0f);

    Material *red = new Lambertian(new ConstantTexture(Color(0.65f, 0.05f, 0.05f)));
    Material *green = new Lambertian(new ConstantTexture(Color(0.12f, 0.45f, 0.15f)));
    Material *white = new Lambertian(new ConstantTexture(Color(0.73f, 0.73f, 0.73f)));
    Material *light = new DiffuseEmitter(new ConstantTexture(Color(15.0f, 15.0f, 15.0f)));

    Intersectable **list = new Intersectable*[10];
    Instance *light_rect = new Instance(translate(343,554,237)*rotate_z(M_PI), new Rectangle(0.0f, 130.0f, 0.0f, 105.0f, 0.0f, 1, light));
    list[0] = light_rect;
    list[1] = new Instance(translate(555,0,555)*rotate_y(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 0, red));
    list[2] = new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 0, green);
    list[3] = new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 1, white);
    list[4] = new Instance(translate(555,555,0)*rotate_z(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 1, white));
    list[5] = new Instance(translate(555,0,555)*rotate_y(M_PI), new Rectangle(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, 2, white));
    list[6] = new Instance(translate(130,0,65)*rotate_y((1.0/6)*M_PI), new Cube(Vec3(0,0,0),Vec3(165,165,165), white));
    list[7] = new Instance(translate(265,0,295)*rotate_y((-1.0/5)*M_PI), new Cube(Vec3(0,0,0),Vec3(165,330,165), white));

    Light ** l_list = new Light*[1];
    l_list[0] = new AreaLight(light_rect, Color(15.0f, 15.0f, 15.0f), Color(100.0f, 98.0f, 88.0f));
    lights = LightList(l_list , 1);

    return new BVHNode(list, 7, 0.0f, 0.0f);
}

#endif
