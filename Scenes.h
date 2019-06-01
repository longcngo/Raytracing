#ifndef SCENESH
#define SCENESH
#define STB_IMAGE_IMPLEMENTATION

#include <cfloat>
#include "stb_image.h"
#include "Shapes.h"
#include "Camera.h"
#include "Material.h"
#include "IntersectList.h"
#include "BoundingVolumeHierarchy.h"
#include "Lights.h"

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

// Intersectable *simple_emitter_scene(Camera& cam, LightList& lights, float x_max, float y_max)
// {
//     Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
//     Vec3 lookat = Vec3(0.25f,0.0f,0.5f);
//     Vec3 vup = Vec3(0.0f,1.0f,0.0f);
//     float dist_to_focus = 10.0f;
//     float aperature = 0.1f;
//     cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);
//
//     Light ** l_list = new Light*[1];
//     SphereLight *spl = new SphereLight(Vec3(1.25f, 0.0f, -1.25f), 1.25f, Color(1.0f, 0.9f, 0.8f), Color(100.0f, 98.0f, 88.0f));
//     l_list[0] = spl;
//     lights = LightList(l_list , 1);
//
//     Intersectable **list = new Intersectable*[3];
//     list[0] = spl->shape;
//     list[1] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(Color(0.5f,0.5f,0.5f)));
//     list[2] = new Sphere(Vec3(-1.25f, 0.0f, 1.25f), 1.25f, new Lambertian(Color(1.0f, 0.2f, 0.2f)));
//     return new IntersectList(list, 3);
// }

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

#endif
