#ifndef MATERIALH
#define MATERIALH

#include "Textures.h"
#include "Ray.h"
#include "Intersection.h"

struct Intersection;

Vec3 random_in_unit_sphere()
{
    Vec3 p;
    do {
        p = 2.0*Vec3(xorandf(), xorandf(), xorandf())-Vec3(1.0f,1.0f,1.0f);
    } while(p.squared_length() >= 1.0);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2*dot(v,n)*n;
}

bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
{
    Vec3 uv = unit_vector(v);
    float dt = dot(uv,n);
    float discriminant = 1.0f-(ni_over_nt*ni_over_nt*(1.0f-(dt*dt)));
    if (discriminant > 0.0f)
    {
        refracted = ni_over_nt*(uv-dt*n)-sqrt(discriminant)*n;
        return true;
    }
    else
    {
        return false;
    }
}

float schlick(float cosine, float ref_idx)
{
    float r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}

class Material
{
public:
    bool isReflective;

    virtual bool scatter(const Ray& r_in, const Intersection& isect, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Texture *albedo;

    Lambertian(Texture* a) { albedo = a; isReflective = false; }
    virtual bool scatter(const Ray& r_in, const Intersection& isect, Color& attenuation, Ray& scattered) const
    {
        Vec3 target = isect.p + isect.normal + random_in_unit_sphere();
        scattered = Ray(isect.p, target-isect.p, r_in.t());
        attenuation = albedo->value(isect.uv, isect.p);
        return true;
    }

};

class Metal : public Material
{
public:
    Texture *albedo;
    float fuzz;

    Metal(Texture* a, float f) { albedo = a; isReflective = true;
         if (f > 1.0f) { fuzz = 1.0f;} else { fuzz = f; } }
    virtual bool scatter(const Ray& r_in, const Intersection& isect, Color& attenuation, Ray& scattered) const
    {
        Vec3 reflected = reflect(r_in.dir, isect.normal);
        scattered = Ray(isect.p, reflected + fuzz*random_in_unit_sphere(), r_in.t());
        attenuation = albedo->value(isect.uv, isect.p);
        return (dot(scattered.dir, isect.normal) > 0);
    }

};

class Dielectric : public Material
{
public:
    float ref_idx;

    Dielectric(float ri) { ref_idx = ri; isReflective = true; }
    virtual bool scatter(const Ray& r_in, const Intersection& isect, Color& attenuation, Ray& scattered) const
    {
        Vec3 outward_normal;
        Vec3 reflected = reflect(unit_vector(r_in.d()), isect.normal);
        float ni_over_nt;
        attenuation = Color(1.0f, 1.0f, 1.0f);
        Vec3 refracted;
        float reflect_prob;
        float cosine;
        if (dot(unit_vector(r_in.d()), isect.normal) > 0)
        {
            outward_normal = -isect.normal;
            ni_over_nt = ref_idx;
            cosine = dot(unit_vector(r_in.d()), isect.normal);
            cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
        }
        else
        {
            outward_normal = isect.normal;
            ni_over_nt = 1.0f/ref_idx;
            cosine = -dot(unit_vector(r_in.d()), isect.normal);
        }
        if (refract(unit_vector(r_in.d()), outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else
        {
            reflect_prob = 1.0f;
        }
        if (xorandf() < reflect_prob)
        {
            scattered = Ray(isect.p, reflected, r_in.t());
        }
        else
        {
            scattered = Ray(isect.p, refracted, r_in.t());
        }
        return true;
    }
};

#endif
