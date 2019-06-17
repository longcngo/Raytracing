#ifndef TEXTURESH
#define TEXTURESH

#include "SolidNoise.h"
#include "Vec2.h"
#include "Color.h"

/*  Textures.h

    A class for texturing surfaces. Every texture uses UV coordinates to
    calculate the color at a certain point.

*/

class Texture
{
public:
    virtual Color value(const Vec2& uv, const Vec3& p) const = 0;
};

// A texture for single colors.
// Essentially a wrapper class.
class ConstantTexture : public Texture
{
public:
    Color col;

    ConstantTexture(){}
    ConstantTexture(const Color& c){ col = c; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    { return col; }
};

// A texture for stripes wth variable width
class StripeTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;
    float width;

    StripeTexture(){}
    StripeTexture(Texture* t0, Texture* t1, float w = 1.0f)
    { texture0 = t0; texture1 = t1; width = 1/w; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        if (sin((M_PI*p.x())*width) > 0)
        {
            return texture0->value(uv, p);
        }
        else
        {
            return texture1->value(uv, p);
        }
    }
};

// A texture for stripes wth variable width and interpolating for a
// smoother look
class SmoothStripeTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;
    float width;

    SmoothStripeTexture(){}
    SmoothStripeTexture(Texture* t0, Texture* t1, float w = 1.0f)
    { texture0 = t0; texture1 = t1; width = 1/w; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float t = 0.5f*width*(1+sin(M_PI*p.x()));
        return lerp(texture0->value(uv, p), texture1->value(uv, p), t);
    }
};

// A texture for checkered patterns
class CheckerTexture : public Texture
{
public:
    Texture *texture0;
    Texture *texture1;
    float width;

    CheckerTexture(){}
    CheckerTexture(Texture* t0, Texture* t1, float w = 10.0f)
    { texture0 = t0; texture1 = t1; width = w; }
    virtual Color value(const Vec2& uv, const Vec3& p) const
    {
        float sines = (sin(width*p.x())*sin(width*p.y())*sin(width*p.z()));
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

// A texture for Perlin noise generation
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

// A texture for turbulance i.e. recursive Perlin noise generation
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

// A texture for striped noise, making it resemble marble
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
        float t = 0.5f*(1+width*sin(scale0*p.x() + scale1*noise.turbulance(p)));
        return lerp(Color(0,0,0), Color(1,1,1), t).clamp();
    }
};

// A texture that maps a 2D image to a 3D surface
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
        // get pixels from image
        int i = int(nx*uv.x());
        int j = int(ny*(1-uv.y()));
        i = i < 0 ? 0 : i;
        j = j < 0 ? 0 : j;
        i = i > nx-1 ? nx-1 : i;
        j = j > ny-1 ? ny-1 : j;

        // extract RGB data from a picture
        Color c0 = Color(data[3*i+3*nx*j],
                         data[3*i+3*nx*j+1],
                         data[3*i+3*nx*j+2])/256.0f;

        // attempted to interpolate neighboring colors, but there is
        // a bug involving float overflows and nans.
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
        // float u1 = nx*uv.x() - floor(nx*uv.x());
        // float v1 = ny*uv.y() - floor(ny*uv.y());
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
