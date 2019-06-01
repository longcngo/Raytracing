#ifndef TEXTURESH
#define TEXTURESH

#include "SolidNoise.h"
#include "Vec2.h"
#include "Color.h"

class Texture
{
public:
    virtual Color value(const Vec2& uv, const Vec3& p) const = 0;
};

class ConstantTexture : public Texture
{
public:
    Color col;

    ConstantTexture(){}
    ConstantTexture(const Color& c){ col = c; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    { return col; }
};

class StripeTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;
    float width;

    StripeTexture(){}
    StripeTexture(Texture* t0, Texture* t1, float w){ texture0 = t0; texture1 = t1; width = 1/w; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        if (sin((M_PI*p.x)*width) > 0)
        {
            return texture0->value(uv, p);
        }
        else
        {
            return texture1->value(uv, p);
        }
    }
};

class SmoothStripeTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;
    float width;

    SmoothStripeTexture(){}
    SmoothStripeTexture(Texture* t0, Texture* t1, float w){ texture0 = t0; texture1 = t1; width = 1/w; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float t = 0.5f*width*(1+sin(M_PI*p.x));
        return lerp(texture0->value(uv, p), texture1->value(uv, p), t);
    }
};

class CheckerTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;

    CheckerTexture(){}
    CheckerTexture(Texture* t0, Texture* t1){ texture0 = t0; texture1 = t1; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float sines = (sin(10*p.x)*sin(10*p.y)*sin(10*p.z));
        if (sines > 0)
        {
            return texture0->value(uv, p);
        }
        else
        {
            return texture1->value(uv, p);
        }
    }
};

class NoiseTexture : public Texture
{
public:
    PerlinNoise noise;
    float scale;

    NoiseTexture(const float s = 1.0f) { scale = s; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float t = 0.5f*(noise.noise(p*scale)+1);
        return lerp(Color(0,0,0), Color(1,1,1), t).clamp();
    }
};

class TurbTexture : public Texture
{
public:
    PerlinNoise noise;
    float scale;

    TurbTexture(const float s = 1.0f) { scale = s; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float t = noise.turbulance(p*scale);
        return lerp(Color(0,0,0), Color(1,1,1), t).clamp();
    }
};

class TurbStripeTexture : public Texture
{
public:
    PerlinNoise noise;
    float width;
    float scale0, scale1;

    TurbStripeTexture(const float w = 1.0f, const float k0 = 1.0f, const float k1 = 1.0f)
    { width = 1/w;  scale0 = k0; scale1 = k1; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float t = 0.5f*(1+width*sin(scale0*p.x + scale1*noise.turbulance(p)));
        return lerp(Color(0,0,0), Color(1,1,1), t).clamp();
    }
};

class ImageTexture : public Texture
{
public:
    unsigned char *data;
    int nx, ny;

    ImageTexture(){}
    ImageTexture(unsigned char *pixels, int na, int nb)
    { data = pixels; nx = na; ny = nb; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        int i = int(nx*uv.x);
        int j = int(ny*(1-uv.y));
        i = i < 0 ? 0 : i;
        j = j < 0 ? 0 : j;
        i = i > nx-1 ? nx-1 : i;
        j = j > ny-1 ? ny-1 : j;

        Color c0 = Color(data[3*i+3*nx*j],
                         data[3*i+3*nx*j+1],
                         data[3*i+3*nx*j+2])/256.0f;

        // Color c1 = Color(data[3*(i+1)+3*nx*j],
        //                  data[3*(i+1)+3*nx*j+1],
        //                  data[3*(i+1)+3*nx*j+2])/256.0f;
        //
        // Color c2 = Color(data[3*i+3*nx*(j+1)],
        //                  data[3*i+3*nx*(j+1)+1],
        //                  data[3*i+3*nx*(j+1)+2])/256.0f;
        //
        // Color c3 = Color(data[3*(i+1)+3*nx*(j+1)],
        //                  data[3*(i+1)+3*nx*(j+1)+1],
        //                  data[3*(i+1)+3*nx*(j+1)+2])/256.0f;
        //
        // float u1 = nx*uv.x - floor(nx*uv.x);
        // float v1 = ny*uv.y - floor(ny*uv.y);
        // float u2 = (-2*u1+3)*u1*u1;
        // float v2 = (-2*v1+3)*v1*v1;
        //
        // Color r = (1-u2)*(1-v2)*c0 +
        //        (u2)*(1-v2)*c1 +
        //        (1-u2)*(v2)*c2 +
        //        (u2)*(v2)*c3;
        return c0;
    }
};

#endif
