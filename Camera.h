#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

/*  Camera.h

    A class to represent a thin-lens camera

*/

Vec3 random_in_unit_disk()
{
    Vec3 p;
    do {
        p = 2.0*Vec3(drand48(), drand48(), 0.0f)-Vec3(1.0f,1.0f,0.0f);
    } while(dot(p,p) >= 1.0);
    return p;
}

class Camera
{
public:
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
    Vec3 u, v, w;
    float lens_radius;
    float time0, time1;

    Camera(float aspect)
    {
        time0 = 0.0f;
        time1 = 0.0f;
        lens_radius = 0.5f;
        float half_height = tan(M_PI*0.25f);
        float half_width = aspect*half_height;
        origin = Vec3(0.0f, 0.0f, -10.0f);
        w = unit_vector(origin-Vec3(0.0f,0.0f,0.0f));
        u = unit_vector(cross(Vec3(0.0f,1.0f,0.0f), w));
        v = cross(w,u);
        lower_left_corner = origin - half_width*u - half_height*v - w;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
    }

    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperature, float focus_dist,
        float t0, float t1)
        {
            time0 = t0;
            time1 = t1;
            lens_radius = aperature/2;
            float theta = vfov*M_PI/180;
            float half_height =  tan(theta/2);
            float half_width = aspect*half_height;
            origin = lookfrom;
            w = unit_vector(lookfrom-lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w,u);
            lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        Ray get_ray(float s, float t)
        {
            Vec3 rd = lens_radius*random_in_unit_disk();
            Vec3 offset = u*rd.x() + v*rd.y();
            float time_rand = time0 + (time1-time0)*xorandf();
            return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset, time_rand);
        }

};

#endif
