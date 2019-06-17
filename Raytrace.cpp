#include <fstream>
#include <cstdio>
#include <cfloat>
#include "Scenes.h"
using namespace std;

/*  Raytracing.cpp

    The main raytacing program, handling the IO and the coloring of each pixel.

    The coloring function is split between direct and indirect lighting to have
    a cleaner look and are seperated anyways for global illumination
    calculations. Scene setup is in its own file also to seperate clutter from
    the main file.

*/

Color background(const Ray& r)
{
    return Color(0.0,0.0,0.0);
    //float t = 0.5*(unit_vector(r.d()).y + 1.0f);
    //return (1.0f-t)*Color(1.0f,1.0f,1.0f) + t*Color(0.5f,0.7f,1.0f);
}

Color direct_lighting(const Intersection& isect, const Ray& r, Intersectable *world, LightList *lights)
{
    Color radiance = Color();
    Intersection isect_shadow;
    LightSample ls;
    Color attenuation;
    int num_lights = lights->list_size;

    for (int i = 0; i < num_lights; i++)
    {
        if (lights->light_list[i]->get_light(isect.p, ls))
        {
            float light_dist = (ls.p-isect.p).squared_length();
            Ray shadow = Ray(isect.p, ls.dir , r.t());
            if (!(world->intersect(shadow, 0.0001f, FLT_MAX, isect_shadow)) ||
                (light_dist < isect_shadow.t) ||
                (isect_shadow.mat->emitted(isect_shadow.uv, isect_shadow.p) != Color()))
            {
                isect.mat->illuminated(isect, radiance);
                float ndotl = dot(isect.normal, ls.dir);
                if (ndotl > 0.0f) {
                    attenuation *= ls.c;
                    radiance += attenuation;
                }
            }
        }
    }

    return radiance;
}

Color indirect_lighting(Intersection& isect, const Ray& r, Intersectable *world, int depth)
{
    Ray scattered;
    Color attenuation;

    if (world->intersect(r, 0.0001f, FLT_MAX, isect))
    {
        Color emitted = isect.mat->emitted(isect.uv, isect.p);
        bool didScatter = isect.mat->scatter(r, isect, attenuation, scattered);
        if (depth < 50 && didScatter)
        {
            return emitted + attenuation*indirect_lighting(isect, scattered, world, ++depth);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return background(r);
    }

}


Color raytrace(const Ray& r, Intersectable *world, LightList *lights)
{
    Intersection isect;
    Color radiance = Color();

    if (world->intersect(r, 0.0001f, FLT_MAX, isect))
    {
        radiance = isect.mat->emitted(isect.uv, isect.p);
        radiance += direct_lighting(isect, r, world, lights);
        radiance += indirect_lighting(isect, r, world, 0);
        return radiance;
    }
    else
    {
        return background(r);
    }

}

void scan_image(ofstream& os, int x_max, int y_max, int samples)
{
    os << "P3\n" << x_max << " " << y_max << "\n255\n";

    Camera cam = Camera(float(x_max)/float(y_max));
    LightList lights;
    Intersectable *world;

    //world = simple_sphere_scene(cam, lights, x_max, y_max);
    //world = simple_triangle_scene(cam, lights, x_max, y_max);
    //world = simple_rect_scene(cam, lights, x_max, y_max);
    world = simple_mesh_scene1(cam, lights, x_max, y_max);
    //world = simple_mesh_scene2(cam, lights, x_max, y_max);
    //world = simple_texture_scene(cam, lights, x_max, y_max);
    //world = simple_perlin_scene(cam, lights, x_max, y_max);
    //world = simple_turb_scene(cam, lights, x_max, y_max);
    //world = simple_earth_scene(cam, lights, x_max, y_max);
    //world = simple_img_test_scene(cam, lights, x_max, y_max);
    //world = simple_spotlight_scene(cam, lights, x_max, y_max);
    //world = simple_mirror_scene(cam, lights, x_max, y_max);
    //world = simple_glass_scene(cam, lights, x_max, y_max);
    //world = simple_emitter_scene1(cam, lights, x_max, y_max);
    //world = simple_emitter_scene2(cam, lights, x_max, y_max);
    //world = three_sphere_scene(cam, lights, x_max, y_max);
    //world = random_scene(cam, lights, x_max, y_max);

    for (int j = y_max-1; j >= 0; j--)
    {
        for (int i = 0; i < x_max; i++)
        {
            Color col = Color(0.0f,0.0f,0.0f);
            for (int s = 0; s < samples; s++)
            {
                float ur = xorandf();
                float vr = xorandf();
                float u = float(i + ur)/float(x_max);
                float v = float(j + vr)/float(y_max);
                Ray r = cam.get_ray(u,v);
                col += raytrace(r, world, &lights);
            }
            col /= float(samples);
            col.clamp();
            col.sqrt();
            col *= 255.99f;
            col.to_int();
            os << col << "\n";
        }
    }

}


int main()
{
    std::clock_t start;
    double duration;

    ofstream outfile;
    outfile.open("output/raytrace_62.ppm", ios::out | ios::trunc);
    int image_w = 300;
    int image_h = 300;
    int samples = 100;

    std::cout << "Settings" << '\n';
    std::cout << "image_w: " << image_w << '\n';
    std::cout << "image_h: " << image_h << '\n';
    std::cout << "samples: " << samples << '\n';
    std::cout << "Raytracing Start!" << '\n';
    xorseed();

    start = std::clock();

    scan_image(outfile, image_w, image_h, samples);

    outfile.close();

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Raytracing End!" << '\n';
    std::cout << "Time Elapsed: " << duration <<'\n';

    ofstream result;
    result.open("output/raytrace_runtime.txt", ios::out | ios::trunc);
    result << "Time Elapsed: " << duration <<'\n';
    result.close();

    return 0;
}
