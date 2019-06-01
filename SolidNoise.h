#ifndef SOLIDNOISEH
#define SOLIDNOISEH

#include "Vec3.h"
#include "RNG.h"

class PerlinNoise
{
public:
    Vec3 grad[256];
    int phi[3][256];

    PerlinNoise()
    {
        int i,j;

        // N=16
        // grad[0] = Vec3(1,1,0);
        // grad[1] = Vec3(-1,1,0);
        // grad[2] = Vec3(1,-1,0);
        // grad[3] = Vec3(-1,-1,0);
        // grad[4] = Vec3(1,0,1);
        // grad[5] = Vec3(-1,0,1);
        // grad[6] = Vec3(1,0,-1);
        // grad[7] = Vec3(-1,0,-1);
        // grad[8] = Vec3(0,1,1);
        // grad[9] = Vec3(0,-1,1);
        // grad[10] = Vec3(0,1,-1);
        // grad[11] = Vec3(0,-1,-1);
        // grad[12] = Vec3(1,1,0);
        // grad[13] = Vec3(-1,1,0);
        // grad[14] = Vec3(0,1,-1);
        // grad[15] = Vec3(0,-1,-1);

        //N=256
        for (i = 0; i < 256; i++) {
            grad[i] = unit_vector(2.0*Vec3(xorandf(), xorandf(), xorandf())-Vec3(1.0f,1.0f,1.0f));
        }

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 256; j++)
            {
                phi[i][j] = j;
            }
        }

        for (i = 0; i < 3; i++)
        {
            for (j = 255; j >= 0; j--)
            {
                int pivot = int(xorandf()*16);
                int temp = phi[i][pivot];
                phi[i][pivot] = phi[i][j];
                phi[i][j] = temp;
            }
        }

    }

    inline float turbulance(const Vec3& p, int depth = 7, float f = 2.0f) const
    {
        float sum = 0.0f;
        float factor = f;
        float inv_factor = 1/f;
        float numerator = 1.0f;
        Vec3 ptemp = p;
        for (int i = 0; i < depth; i++)
        {
            sum += fabs(noise(ptemp))*numerator;
            ptemp *= factor;
            numerator *= inv_factor;
        }
        return sum;
    }

    inline float noise(const Vec3& p) const
    {
        int fi = int(floor(p.x));
        int fj = int(floor(p.y));
        int fk = int(floor(p.z));

        float fx = p.x - floor(p.x);
        float fy = p.y - floor(p.y);
        float fz = p.z - floor(p.z);

        float sum = 0.0f;
        Vec3 v;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    v = Vec3(fx-i, fy-j, fz-k);
                    sum += knot(fi+i, fj+j, fk+k, v);
                }
            }
        }

        return sum;

    }

    inline float knot(int i, int j, int k, Vec3& v) const
    {
        Vec3 unit = gamma(i,j,k);
        return omega(v.x)*omega(v.y)*omega(v.z)*dot(unit, v);
    }

    inline float omega(float t) const
    {
        t = t < 0 ? -t : t;
        return t*t*(2*t-3)+1;
    }

    inline Vec3 gamma(int i, int j, int k) const
    {
        return grad[phi[0][i & 255] ^ phi[1][j & 255] ^ phi[2][k & 255]];
    }

};




#endif
