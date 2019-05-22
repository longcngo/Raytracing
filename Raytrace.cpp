#include <fstream>
#include <iostream>
#include <cfloat>
#include "Shapes.h"
#include "Camera.h"
#include "Material.h"
#include "IntersectList.h"
using namespace std;

Color raytrace(const Ray& r, Intersectable *world, int depth)
{
  Intersection isect;
  if (world->intersect(r, 0.0001f, FLT_MAX, isect))
  {
    Ray scattered;
    Color attenuation;
    if (depth < 50 && isect.mat->scatter(r, isect, attenuation, scattered))
    {
      depth += 1;
      Color new_attenuation = raytrace(scattered, world, depth);
      return attenuation*new_attenuation;
    }
    else
    {
      return Color(0.0f,0.0f,0.0f);
    }
  }
  else
  {
    float t = 0.5*(unit_vector(r.d()).y + 1.0f);
    return (1.0f-t)*Color(1.0f,1.0f,1.0f) + t*Color(0.5f,0.7f,1.0f);
  }
}

Intersectable *random_scene(Camera& cam, float x_max, float y_max)
{
  Vec3 lookfrom = Vec3(13.0f, 2.0f, 3.0f);
  Vec3 lookat = Vec3(0.0f,0.0f,0.0f);
  Vec3 vup = Vec3(0.0f,1.0f,0.0f);
  float dist_to_focus = 10.0f;
  float aperature = 0.1f;
  cam = Camera(lookfrom, lookat, vup, 20.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

  int n = 50000;
  Intersectable **list = new Intersectable*[n+1];
  list[0] = new Sphere(Vec3(0.0f,-1000.0f, 0.0f), 1000.0f, new Lambertian(Color(0.5f,0.5f,0.5f)));
  int i = 1;
  Material *sphere_mat_ptr;

  for (int a = -10; a < 10; a++) {
    for (int b = -10; b < 10; b++) {

      float choose_mat = drand48();
      Vec3 cen = Vec3(a+0.9f*drand48(),0.2f,b+0.9f*drand48());
      if ((cen-Vec3(4.0f,0.2f,0.0f)).length() > 0.9) {
        if (choose_mat < 0.8) // diffuse
        {
          sphere_mat_ptr = new Lambertian(Color(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()));
          list[i++] = new MovingSphere(cen, (cen+Vec3(0.0f, 0.5f*drand48(), 0.0f)), 0, 1, 0.2f, sphere_mat_ptr);
        }
        else if (choose_mat < 0.95) //metal
        {
          sphere_mat_ptr = new Metal(Color(0.5f*(1+drand48()), 0.5f*(1+drand48()), 0.5f*(1+drand48())), 0.5*drand48());
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

  list[i++] = new Sphere(Vec3(-4.0f,1.0f,0.0f), 1.0f, new Lambertian(Color(0.4f,0.2f,0.1f)));
  list[i++] = new Sphere(Vec3(0.0f,1.0f,0.0f), 1.0f, new Dielectric(1.5));
  list[i++] = new Sphere(Vec3(4.0f,1.0f,0.0f), 1.0f, new Metal(Color(0.7f,0.6f,0.5f), 0.0f));

  return new IntersectList(list, i);
}

Intersectable *simple_sphere_scene(Camera& cam, float x_max, float y_max)
{
  Vec3 lookfrom = Vec3(8.0f, 5.0f, 9.0f);
  Vec3 lookat = Vec3(-0.15f,0.0f,0.5f);
  Vec3 vup = Vec3(0.0f,1.0f,0.0f);
  float dist_to_focus = 10.0f;
  float aperature = 0.1f;
  cam = Camera(lookfrom, lookat, vup, 30.0f, float(x_max)/float(y_max), aperature, dist_to_focus, 0, 1);

  Intersectable **list = new Intersectable*[2];
  list[0] = new Sphere(Vec3(0.0f,-1001.25f, 0.0f), 1000.0f, new Lambertian(Color(0.5f,0.5f,0.5f)));
  list[1] = new Sphere(Vec3(-0.25f, 0.0f, 0.25f), 1.25f, new Lambertian(Color(1.0f, 0.2f, 0.2f)));

  return new IntersectList(list, 2);
}


void scan_image(int x_max, int y_max, int samples)
{

  ofstream outfile;
  outfile.open("output/raytrace_24.ppm", ios::out | ios::trunc);
  outfile << "P3\n" << x_max << " " << y_max << "\n255\n";

  // Intersectable *list[5];
  // list[0] = new Sphere(Vec3(0.0f,0.0f,-1.0f), 0.5f, new Lambertian(Color(0.1f,0.2f,0.5f)));
  // list[1] = new Sphere(Vec3(0.0f,-100.5f,-1.0f), 100.0f, new Lambertian(Color(0.8f,0.8f,0.0f)));
  // list[2] = new Sphere(Vec3(1.0f,0.0f,-1.0f), 0.5f, new Metal(Color(0.8f,0.6f,0.2f), 0.3f));
  // list[3] = new Sphere(Vec3(-1.0f,0.0f,-1.0f), 0.5f, new Dielectric(1.5f));
  // list[4] = new Sphere(Vec3(-1.0f,0.0f,-1.0f), -0.45f, new Dielectric(1.5f));
  // Intersectable *world = new IntersectList(list, 5);

  // float R = cos(M_PI/4);
  // Intersectable *list[2];
  // list[0] = new Sphere(Vec3(-R,0.0f,-1.0f), R, new Lambertian(Color(1.0f,0.2f,0.0f)));
  // list[1] = new Sphere(Vec3(R,0.0f,-1.0f), R, new Lambertian(Color(0.0f,0.2f,1.0f)));
  // Intersectable *world = new IntersectList(list, 2);

  Camera cam = Camera(float(x_max)/float(y_max));
  Intersectable *world;

  world = simple_sphere_scene(cam, x_max, y_max);
  //world = random_scene(cam, x_max, y_max);

  for (int j = y_max-1; j >= 0; j--) {
    for (int i = 0; i < x_max; i++) {
      Color col = Color(0.0f,0.0f,0.0f);
      for (int s = 0; s < samples; s++)
      {
        float ur = drand48();
        float vr = drand48();
        float u = float(i + ur)/float(x_max);
        float v = float(j + vr)/float(y_max);
        // std::cout << "u " << u << "\n";
        // std::cout << "v " << v << "\n";
        // std::cout << "ur " << ur << "\n";
        // std::cout << "vr " << vr << "\n";
        Ray r = cam.get_ray(u,v);
        col += raytrace(r, world, 0);
      }
      col /= float(samples);
      col.sqrt();
      col *= 255.99f;
      col.to_int();
      outfile << col << "\n";
    }
  }

  outfile.close();
  //stbi_write_png("raytrace.png", x_max, y_max, int comp, const void *data, int stride_in_bytes);
}


int main()
{
  scan_image(200, 200, 100);
  return 0;
}
