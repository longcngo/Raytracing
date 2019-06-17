#ifndef ORTHONORMALBASISH
#define ORTHONORMALBASISH

#define ONB_EPSILON 0.0001f

#include "Vec3.h"

/*  OrthonormalBasis.h

    A class for customized bases.

    As there is a need to use different cordinate systems e.g. camera to world
    space, a ONB class would be useful.

*/

class ONB
{
public:
    Vec3 u,v,w;

    ONB(){}
    ONB(const Vec3& a, const Vec3& b, const Vec3& c)
    { u = a; v = b; w = c;
      u.normalize(); v.normalize(); w.normalize(); }

    // construct ONB from u
    void initU(const Vec3& a)
    {
        Vec3 m = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 n = Vec3(0.0f, 1.0f, 0.0f);
        u = unit_vector(a);
        v = cross(u,n);
        v = v.length() < ONB_EPSILON ? cross(u,m) : v;
        w = cross(u,v);
    }
    // construct ONB from v
    void initV(const Vec3& b)
    {
        Vec3 m = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 n = Vec3(0.0f, 1.0f, 0.0f);
        v = unit_vector(b);
        u = cross(v,n);
        u = u.length() < ONB_EPSILON ? cross(v,m) : u;
        w = cross(u,v);
    }
    // construct ONB from w
    void initW(const Vec3& c)
    {
        Vec3 m = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 n = Vec3(0.0f, 1.0f, 0.0f);
        w = unit_vector(c);
        u = cross(w,n);
        u = u.length() < ONB_EPSILON ? cross(w,m) : u;
        v = cross(w,u);
    }
    // construct ONB from u and v
    void initUV(const Vec3& a, const Vec3& b)
    {
        u = unit_vector(a);
        w = unit_vector(cross(a,b));
        v = cross(w,u);
    }
    // construct ONB from v and u
    void initVU(const Vec3& b, const Vec3& a)
    {
        v = unit_vector(b);
        w = unit_vector(cross(a,b));
        u = cross(v,w);
    }
    // construct ONB from u and w
    void initUW(const Vec3& a, const Vec3& c)
    {
        u = unit_vector(a);
        v = unit_vector(cross(a,c));
        w = cross(u,v);
    }
    // construct ONB from w and u
    void initWU(const Vec3& c, const Vec3& a)
    {
        w = unit_vector(c);
        v = unit_vector(cross(a,c));
        u = cross(v,w);
    }
    // construct ONB from v and w
    void initVW(const Vec3& b, const Vec3& c)
    {
        v = unit_vector(b);
        u = unit_vector(cross(b,c));
        w = cross(u,v);
    }
    // construct ONB from w and v
    void initWV(const Vec3& c, const Vec3& b)
    {
        w = unit_vector(c);
        u = unit_vector(cross(b,c));
        v = cross(w,u);
    }
    // construct ONB from u, v, and w
    void setUVW(const Vec3& a, const Vec3& b, const Vec3& c)
    { u = a; v = b; w = c;
      u.normalize(); v.normalize(); w.normalize(); }

    inline Vec3 local(const Vec3& a) const
    {
        return a.x()*u + a.y()*v + a.z()*w;
    }

    inline Vec3 local(const float a, const float b, const float c) const
    {
        return a*u + b*v + c*w;
    }

};

inline std::istream& operator>>(std::istream& is, ONB& t)
{
    is >> t.u >> t.v >> t.w;
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const ONB& t)
{
    os << t.u << "\n" << t.v << "\n" << t.w << "\n";
    return os;
}

inline bool operator==(const ONB& o1, const ONB& o2)
{
    return ((o1.u == o2.u) && (o1.v == o2.v) && (o1.w == o2.w));
}

inline bool operator!=(const ONB& o1, const ONB& o2)
{
    return ((o1.u != o2.u) || (o1.v != o2.v)|| (o1.w != o2.w));
}

#endif
