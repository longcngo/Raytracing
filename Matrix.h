#pragma once
#include "Vec3.h"

/*  Matrix.h

    A class that represents a 4x4 matrix of floats.

    This class is mainly for transformatons and viewing hence the functions for
    those.

*/

class Matrix
{
public:
    // sixteen elements
    float m[4][4];

    // constructors
    Matrix(){}
    Matrix(const float a, const float b, const float c, const float d,
           const float e, const float f, const float g, const float h,
           const float i, const float j, const float k, const float l)
    {
        m[0][0] = a; m[0][1] = b; m[0][2] = c; m[0][3] = d;
        m[1][0] = e; m[1][1] = f; m[1][2] = g; m[1][3] = h;
        m[2][0] = i; m[2][1] = j; m[2][2] = k; m[2][3] = l;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    };
    Matrix(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        m[0][0] = a.x(); m[0][1] = b.x(); m[0][2] = c.x(); m[0][3] = 0.0f;
        m[1][0] = a.y(); m[1][1] = b.y(); m[1][2] = c.y(); m[1][3] = 0.0f;
        m[2][0] = a.z(); m[2][1] = b.z(); m[2][2] = c.z(); m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    };
    Matrix(const Matrix& mm)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i][j] = mm.m[i][j];
            }
        }
    };

    // binary operators
    inline Matrix& operator+=(const Matrix& mat);
    inline Matrix& operator-=(const Matrix& mat);
    inline Matrix& operator*=(const Matrix& mat);
    inline Matrix& operator*=(float t);
    inline Matrix& operator/=(float t);

    inline Vec3 loc_transform(const Matrix& mat, const Vec3& vec);
    inline Vec3 vec_transform(const Matrix& mat, const Vec3& vec);

    inline Matrix zero();
    inline Matrix identity();
    inline Matrix translate(float x, float y, float z);
    inline Matrix scale(float x, float y, float z);
    inline Matrix rotate(const Vec3& axis, float angle);
    inline Matrix rotate_x(float angle);
    inline Matrix rotate_y(float angle);
    inline Matrix rotate_z(float angle);
    inline Matrix view_mat(const Vec3& eye, const Vec3& gaze, const Vec3& up);

    inline float determinant();
    inline void transpose();
    inline void inverse();

    inline Matrix transpose_mat() const;
    inline Matrix inverse_mat() const;

    inline float det3(const float a, const float b, const float c,
                      const float d, const float e, const float f,
                      const float g, const float h, const float i)
    {
        return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f;
    }

};

inline std::istream& operator>>(std::istream &is, Matrix &t)
{
    is >> t.m[0][0] >> t.m[0][1] >> t.m[0][2] >> t.m[0][3]
       >> t.m[1][0] >> t.m[1][1] >> t.m[1][2] >> t.m[1][3]
       >> t.m[2][0] >> t.m[2][1] >> t.m[2][2] >> t.m[2][3]
       >> t.m[3][0] >> t.m[3][1] >> t.m[3][2] >> t.m[3][3];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Matrix &t)
{
    os << t.m[0][0] << " " << t.m[0][1] << " " << t.m[0][2] << " " << t.m[0][3] << "/n"
       << t.m[1][0] << " " << t.m[1][1] << " " << t.m[1][2] << " " << t.m[1][3] << "/n"
       << t.m[2][0] << " " << t.m[2][1] << " " << t.m[2][2] << " " << t.m[2][3] << "/n"
       << t.m[3][0] << " " << t.m[3][1] << " " << t.m[3][2] << " " << t.m[3][3];
    return os;
}

inline Matrix operator+(const Matrix& mat1, const Matrix& mat2)
{
    Matrix ret;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ret.m[i][j] = mat1.m[i][j] + mat2.m[i][j];
        }
    }

    return ret;
}

inline Matrix operator-(const Matrix& mat1, const Matrix& mat2)
{
    Matrix ret;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ret.m[i][j] = mat1.m[i][j] - mat2.m[i][j];
        }
    }

    return ret;
}

inline Matrix operator*(const Matrix& mat1, const Matrix& mat2)
{
    Matrix ret;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                sum += mat1.m[i][k] * mat2.m[k][j];
            }
            ret.m[i][j] = sum;
        }
    }

    return ret;
}

inline Vec3 operator*(const Matrix& mat, const Vec3& vec)
{
    Vec3 ret;
    float temp;

    ret[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2] + mat.m[0][3];
    ret[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2] + mat.m[1][3];
    ret[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2] + mat.m[2][3];
    temp = vec[0]*mat.m[3][0] + vec[1]*mat.m[3][1] + vec[2]*mat.m[3][2] + mat.m[3][3];
    ret /= temp;

    return ret;
}

inline Matrix operator*(const Matrix& mat, float t)
{
    Matrix ret;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ret.m[i][j] = mat.m[i][j] * t;
        }
    }

    return ret;
}

inline Matrix operator/(const Matrix& mat, float t)
{
    Matrix ret;
    float k = 1/t;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ret.m[i][j] = mat.m[i][j] * k;
        }
    }

    return ret;
}

inline Matrix& Matrix::operator+=(const Matrix& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] += mat.m[i][j];
        }
    }

    return *this;
}

inline Matrix& Matrix::operator-=(const Matrix& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] -= mat.m[i][j];
        }
    }

    return *this;
}

inline Matrix& Matrix::operator*=(const Matrix& mat)
{
    Matrix ret = *this;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                sum += ret.m[i][k] * mat.m[k][j];
            }
            m[i][j] = sum;
        }
    }

    return *this;
}

inline Matrix& Matrix::operator*=(float t)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] *= t;
        }
    }

    return *this;
}

inline Matrix& Matrix::operator/=(float t)
{
    float k = 1/t;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] *= k;
        }
    }

    return *this;
}

inline Vec3 loc_transform(const Matrix& mat, const Vec3& vec)
{
    return mat*vec;
}

inline Vec3 vec_transform(const Matrix& mat, const Vec3& vec)
{
    Vec3 ret;

    ret[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2];
    ret[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2];
    ret[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2];

    return ret;
}

inline Matrix zero()
{
    Matrix ret;

    ret.m[0][0] = ret.m[0][1] = ret.m[0][2] = ret.m[0][3] =
    ret.m[1][0] = ret.m[1][1] = ret.m[1][2] = ret.m[1][3] =
    ret.m[2][0] = ret.m[2][1] = ret.m[2][2] = ret.m[2][3] =
    ret.m[3][0] = ret.m[3][1] = ret.m[3][2] = ret.m[3][3] = 0.0f;

    return ret;
}

inline Matrix identity()
{
    Matrix ret;

    ret.m[0][0] = 1.0f; ret.m[0][1] = 0.0f; ret.m[0][2] = 0.0f; ret.m[0][3] = 0.0f;
    ret.m[1][0] = 0.0f; ret.m[1][1] = 1.0f; ret.m[1][2] = 0.0f; ret.m[1][3] = 0.0f;
    ret.m[2][0] = 0.0f; ret.m[2][1] = 0.0f; ret.m[2][2] = 1.0f; ret.m[2][3] = 0.0f;
    ret.m[3][0] = 0.0f; ret.m[3][1] = 0.0f; ret.m[3][2] = 0.0f; ret.m[3][3] = 1.0f;

    return ret;
}

inline Matrix translate(float x, float y, float z)
{
    Matrix ret = identity();

    ret.m[0][3] = x;
    ret.m[1][3] = y;
    ret.m[2][3] = z;

    return ret;
}

inline Matrix scale(float x, float y, float z)
{
    Matrix ret = identity();

    ret.m[0][0] = x;
    ret.m[1][1] = y;
    ret.m[2][2] = z;

    return ret;
}

inline Matrix rotate(const Vec3& axis, float angle)
{
    Matrix ret = identity();
    Vec3 ax = unit_vector(axis);
    float x = ax.x();
    float y = ax.y();
    float z = ax.z();
    float cosine = cos(angle);
    float sine = sin(angle);
    float t = 1-cosine;

    ret.m[0][0] = t*x*x + cosine;
    ret.m[0][1] = t*x*y - sine*z;
    ret.m[0][2] = t*x*z + sine*y;
    ret.m[0][3] = 0.0f;

    ret.m[1][0] = t*y*x + sine*z;
    ret.m[1][1] = t*y*y + cosine;
    ret.m[1][2] = t*y*z - sine*x;
    ret.m[1][3] = 0.0f;

    ret.m[2][0] = t*z*x - sine*y;
    ret.m[2][1] = t*z*y + sine*x;
    ret.m[2][2] = t*z*z + cosine;
    ret.m[2][3] = 0.0f;

    ret.m[3][0] = 0.0f;
    ret.m[3][1] = 0.0f;
    ret.m[3][2] = 0.0f;
    ret.m[3][3] = 1.0f;

    return ret;
}

inline Matrix rotate_x(float angle)
{
    Matrix ret = identity();
    float cosine = cos(angle);
    float sine = sin(angle);

    ret.m[1][1] = cosine;
    ret.m[1][2] = -sine;
    ret.m[2][1] = sine;
    ret.m[2][2] = cosine;

    return ret;
}

inline Matrix rotate_y(float angle)
{
    Matrix ret = identity();
    float cosine = cos(angle);
    float sine = sin(angle);

    ret.m[0][0] = cosine;
    ret.m[0][2] = sine;
    ret.m[2][0] = -sine;
    ret.m[2][2] = cosine;

    return ret;
}

inline Matrix rotate_z(float angle)
{
    Matrix ret = identity();
    float cosine = cos(angle);
    float sine = sin(angle);

    ret.m[0][0] = cosine;
    ret.m[0][1] = -sine;
    ret.m[1][0] = sine;
    ret.m[1][1] = cosine;

    return ret;
}

inline Matrix view_mat(const Vec3& eye, const Vec3& gaze, const Vec3& up)
{
    // ONB basis based on params
    Vec3 w = -unit_vector(gaze);
    Vec3 u = unit_vector(cross(up,w));
    Vec3 v = cross(w,u);

    // Rotate uvw basis to xyz  basis
    Matrix ret = Matrix(u,v,w);

    // Translate eye to xyz origin
    Matrix move = identity();
    move.m[0][3] = -(eye.x());
    move.m[1][3] = -(eye.y());
    move.m[2][3] = -(eye.z());

    ret = ret*move;
    return ret;
}

inline float Matrix::determinant()
{
    float det;

    det =  m[0][0] * det3(m[1][1], m[1][2], m[1][3],
                          m[2][1], m[2][2], m[2][3],
                          m[3][1], m[3][2], m[3][3]);

    det -= m[0][1] * det3(m[1][0], m[1][2], m[1][3],
                          m[2][0], m[2][2], m[2][3],
                          m[3][0], m[3][2], m[3][3]);

    det += m[0][2] * det3(m[1][0], m[1][1], m[1][3],
                          m[2][0], m[2][1], m[2][3],
                          m[3][0], m[3][1], m[3][3]);

    det -= m[0][3] * det3(m[1][0], m[1][1], m[1][2],
                          m[2][0], m[2][1], m[2][2],
                          m[3][0], m[3][1], m[3][2]);

    return det;
}

inline void Matrix::transpose()
{
    Matrix tranpose;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tranpose.m[i][j] = m[j][i];
        }
    }

    *this = tranpose;
}

inline void Matrix::inverse()
{
    float det = 1/determinant();
    Matrix inverse;

    inverse.m[0][0] =  det3(m[1][1], m[1][2], m[1][3],
                            m[2][1], m[2][2], m[2][3],
                            m[3][1], m[3][2], m[3][3]) * det;
    inverse.m[0][1] = -det3(m[0][1], m[0][2], m[0][3],
                            m[2][1], m[2][2], m[2][3],
                            m[3][1], m[3][2], m[3][3]) * det;
    inverse.m[0][2] =  det3(m[0][1], m[0][2], m[0][3],
                            m[1][1], m[1][2], m[1][3],
                            m[3][1], m[3][2], m[3][3]) * det;
    inverse.m[0][3] = -det3(m[0][1], m[0][2], m[0][3],
                            m[1][1], m[1][2], m[1][3],
                            m[2][1], m[2][2], m[2][3]) * det;

    inverse.m[1][0] = -det3(m[1][0], m[1][2], m[1][3],
                            m[2][0], m[2][2], m[2][3],
                            m[3][0], m[3][2], m[3][3]) * det;
    inverse.m[1][1] =  det3(m[0][0], m[0][2], m[0][3],
                            m[2][0], m[2][2], m[2][3],
                            m[3][0], m[3][2], m[3][3]) * det;
    inverse.m[1][2] = -det3(m[0][0], m[0][2], m[0][3],
                            m[1][0], m[1][2], m[1][3],
                            m[3][0], m[3][2], m[3][3]) * det;
    inverse.m[1][3] =  det3(m[0][0], m[0][2], m[0][3],
                            m[1][0], m[1][2], m[1][3],
                            m[2][0], m[2][2], m[2][3]) * det;

    inverse.m[2][0] =  det3(m[1][0], m[1][1], m[1][3],
                            m[2][0], m[2][1], m[2][3],
                            m[3][0], m[3][1], m[3][3]) * det;
    inverse.m[2][1] = -det3(m[0][0], m[0][1], m[0][3],
                            m[2][0], m[2][1], m[2][3],
                            m[3][0], m[3][1], m[3][3]) * det;
    inverse.m[2][2] =  det3(m[0][0], m[0][1], m[0][3],
                            m[1][0], m[1][1], m[1][3],
                            m[3][0], m[3][1], m[3][3]) * det;
    inverse.m[2][3] = -det3(m[0][0], m[0][1], m[0][3],
                            m[1][0], m[1][1], m[1][3],
                            m[2][0], m[2][1], m[2][3]) * det;

    inverse.m[3][0] = -det3(m[1][0], m[1][1], m[1][2],
                            m[2][0], m[2][1], m[2][2],
                            m[3][0], m[3][1], m[3][2]) * det;
    inverse.m[3][1] =  det3(m[0][0], m[0][1], m[0][2],
                            m[2][0], m[2][1], m[2][2],
                            m[3][0], m[3][1], m[3][2]) * det;
    inverse.m[3][2] = -det3(m[0][0], m[0][1], m[0][2],
                            m[1][0], m[1][1], m[1][2],
                            m[3][0], m[3][1], m[3][2]) * det;
    inverse.m[3][3] =  det3(m[0][0], m[0][1], m[0][2],
                            m[1][0], m[1][1], m[1][2],
                            m[2][0], m[2][1], m[2][2]) * det;

    *this = inverse;
}

inline Matrix Matrix::transpose_mat() const
{
    Matrix ret = *this;
    ret.transpose();
    return ret;
}

inline Matrix Matrix::inverse_mat() const
{
    Matrix ret = *this;
    ret.inverse();
    return ret;
}
