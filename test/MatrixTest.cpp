#include "Catch.hpp"
#include "../Matrix.h"

TEST_CASE( "Matrix Initalizations", "[matrix]" )
{
    SECTION( "Float Init" )
    {
        Matrix mat1 = Matrix(1.0f,2.0f,3.0f,4.0f,
                             5.0f,6.0f,7.0f,8.0f,
                             9.0f,10.0f,11.0f,12.0f);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == i*4 + j+1);
            }
        }

        REQUIRE(mat1.m[3][0] == 0.0f);
        REQUIRE(mat1.m[3][1] == 0.0f);
        REQUIRE(mat1.m[3][2] == 0.0f);
        REQUIRE(mat1.m[3][3] == 1.0f);
    }

    SECTION( "Vec3 Init" )
    {
        Vec3 a = Vec3(1.0f,4.0f,7.0f);
        Vec3 b = Vec3(2.0f,5.0f,8.0f);
        Vec3 c = Vec3(3.0f,6.0f,9.0f);

        Matrix mat2 = Matrix(a,b,c);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                REQUIRE(mat2.m[i][j] == i*3 + j+1);
            }
        }

        REQUIRE(mat2.m[0][3] == 0.0f);
        REQUIRE(mat2.m[1][3] == 0.0f);
        REQUIRE(mat2.m[2][3] == 0.0f);
        REQUIRE(mat2.m[3][0] == 0.0f);
        REQUIRE(mat2.m[3][1] == 0.0f);
        REQUIRE(mat2.m[3][2] == 0.0f);
        REQUIRE(mat2.m[3][3] == 1.0f);
    }

    SECTION( "Matrix Init" )
    {
        Matrix mat1 = Matrix(1.0f,2.0f,3.0f,4.0f,
                             5.0f,6.0f,7.0f,8.0f,
                             9.0f,10.0f,11.0f,12.0f);
        Matrix mat2 = Matrix(mat1);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[i][j]);
            }
        }
    }
}

TEST_CASE( "Generated Matricies", "[matrix]" )
{
    SECTION( "Zero" )
    {
        Matrix mat1 = zero();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(0.0f));
            }
        }
    }

    SECTION( "Identity" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    REQUIRE(mat1.m[i][j] == Approx(1.0f));
                }
                else
                {
                    REQUIRE(mat1.m[i][j] == Approx(0.0f));
                }
            }
        }
    }

    SECTION( "Translate" )
    {
        Matrix mat1 = translate(1.0f,2.0f,3.0f);
        Matrix mat2 = identity();

        mat2.m[0][3] = 1.0f;
        mat2.m[1][3] = 2.0f;
        mat2.m[2][3] = 3.0f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[i][j]);
            }
        }
    }

    SECTION( "Translate Nans" )
    {
        Matrix mat1 = translate(0.000000123f,0.000000145f,0.000000138f);
        Matrix mat2 = identity();

        mat2.m[0][3] = 0.000000123f;
        mat2.m[1][3] = 0.000000145f;
        mat2.m[2][3] = 0.000000138f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[i][j]);
            }
        }
    }

    SECTION( "Scale" )
    {
        Matrix mat1 = scale(2.0f,5.0f,10.0f);
        Matrix mat2 = identity();

        mat2.m[0][0] = 2.0f;
        mat2.m[1][1] = 5.0f;
        mat2.m[2][2] = 10.0f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[i][j]);
            }
        }
    }

    SECTION( "Scale Nans" )
    {
        Matrix mat1 = scale(0.0000001f,0.0000001f,0.0000001f);
        Matrix mat2 = identity();

        mat2.m[0][0] = 0.0000001f;
        mat2.m[1][1] = 0.0000001f;
        mat2.m[2][2] = 0.0000001f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[i][j]);
            }
        }
    }

    SECTION( "Rotate Single Axises" )
    {
        Matrix mat1 = rotate_x(M_PI);
        Matrix mat2 = identity();
        float cosine = cos(M_PI);
        float sine = sin(M_PI);
        mat2.m[1][1] = cosine;
        mat2.m[1][2] = -sine;
        mat2.m[2][1] = sine;
        mat2.m[2][2] = cosine;

        Matrix mat3 = rotate_y(2.0f*M_PI);
        Matrix mat4 = identity();
        cosine = cos(2.0f*M_PI);
        sine = sin(2.0f*M_PI);
        mat4.m[0][0] = cosine;
        mat4.m[0][2] = sine;
        mat4.m[2][0] = -sine;
        mat4.m[2][2] = cosine;

        Matrix mat5 = rotate_z(0.5f*M_PI);
        Matrix mat6 = identity();
        cosine = cos(0.5f*M_PI);
        sine = sin(0.5f*M_PI);
        mat6.m[0][0] = cosine;
        mat6.m[0][1] = -sine;
        mat6.m[1][0] = sine;
        mat6.m[1][1] = cosine;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[i][j]).margin(0.001f));
                REQUIRE(mat3.m[i][j] == Approx(mat4.m[i][j]).margin(0.001f));
                REQUIRE(mat5.m[i][j] == Approx(mat6.m[i][j]).margin(0.001f));
            }
        }
    }

    SECTION( "Rotate Single Axises Random" )
    {
        float ang1 = (2.0f*drand48())*M_PI;
        float ang2 = (2.0f*drand48())*M_PI;
        float ang3 = (2.0f*drand48())*M_PI;

        Matrix mat1 = rotate_x(ang1);
        Matrix mat2 = identity();
        float cosine = cos(ang1);
        float sine = sin(ang1);
        mat2.m[1][1] = cosine;
        mat2.m[1][2] = -sine;
        mat2.m[2][1] = sine;
        mat2.m[2][2] = cosine;

        Matrix mat3 = rotate_y(ang2);
        Matrix mat4 = identity();
        cosine = cos(ang2);
        sine = sin(ang2);
        mat4.m[0][0] = cosine;
        mat4.m[0][2] = sine;
        mat4.m[2][0] = -sine;
        mat4.m[2][2] = cosine;

        Matrix mat5 = rotate_z(ang3);
        Matrix mat6 = identity();
        cosine = cos(ang3);
        sine = sin(ang3);
        mat6.m[0][0] = cosine;
        mat6.m[0][1] = -sine;
        mat6.m[1][0] = sine;
        mat6.m[1][1] = cosine;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[i][j]).margin(0.001f));
                REQUIRE(mat3.m[i][j] == Approx(mat4.m[i][j]).margin(0.001f));
                REQUIRE(mat5.m[i][j] == Approx(mat6.m[i][j]).margin(0.001f));
            }
        }
    }

    SECTION( "Rotate Arbitrary Axises" )
    {
        Matrix mat1 = rotate_x(M_PI);
        Matrix mat2 = rotate(Vec3(1.0f,0.0f,0.0f), M_PI);

        Matrix mat3 = rotate_y(2.0f*M_PI);
        Matrix mat4 = rotate(Vec3(0.0f,1.0f,0.0f), 2.0f*M_PI);

        Matrix mat5 = rotate_z(0.5f*M_PI);
        Matrix mat6 = rotate(Vec3(0.0f,0.0f,1.0f), 0.5f*M_PI);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[i][j]));
                REQUIRE(mat3.m[i][j] == Approx(mat4.m[i][j]));
                REQUIRE(mat5.m[i][j] == Approx(mat6.m[i][j]));
            }
        }
    }

    SECTION( "Rotate Arbitrary Axises Random" )
    {
        float ang1 = (2.0f*drand48())*M_PI;
        float ang2 = (2.0f*drand48())*M_PI;
        float ang3 = (2.0f*drand48())*M_PI;

        Matrix mat1 = rotate_x(ang1);
        Matrix mat2 = rotate(Vec3(1.0f,0.0f,0.0f), ang1);

        Matrix mat3 = rotate_y(ang2);
        Matrix mat4 = rotate(Vec3(0.0f,1.0f,0.0f), ang2);

        Matrix mat5 = rotate_z(ang3);
        Matrix mat6 = rotate(Vec3(0.0f,0.0f,1.0f), ang3);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[i][j]));
                REQUIRE(mat3.m[i][j] == Approx(mat4.m[i][j]));
                REQUIRE(mat5.m[i][j] == Approx(mat6.m[i][j]));
            }
        }
    }
}

TEST_CASE( "Matrix IO", "[matrix]" )
{

    // SECTION( "Input" )
    // {
    //     Matrix mat1 = Matrix(1.0f,2.0f,3.0f,4.0f,
    //                          5.0f,6.0f,7.0f,8.0f,
    //                          9.0f,10.0f,11.0f,12.0f,
    //                          13.0f,14.0f,15.0f,16.0f);
    //     Matrix mat2;
    //
    //     std::istream is;
    //     is >> mat1;
    // }
    //
    // SECTION( "Output" )
    // {
    //     Matrix mat1 = Matrix(1.0f,2.0f,3.0f,4.0f,
    //                          5.0f,6.0f,7.0f,8.0f,
    //                          9.0f,10.0f,11.0f,12.0f);
    //
    //     std::ostream os;
    //
    // }

}

TEST_CASE( "Update Matrix Binary Operations", "[matrix]" )
{
    SECTION( "Addition Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = Matrix(mat1);
        mat1 += mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat3.m[i][j] + mat2.m[i][j]) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Addition Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = Matrix(mat1);
        mat1 += mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat3.m[i][j] + mat2.m[i][j]) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Subtraction Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = identity();
        mat1 -= mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat3.m[i][j] - mat2.m[i][j]) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Subtraction Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = Matrix(mat1);
        mat1 -= mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat3.m[i][j] - mat2.m[i][j]) == Approx(mat1.m[i][j]));
            }
        }
    }


    SECTION( "Scalar Multiplication Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        float t = 5.0f;
        mat1 *= t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat2.m[i][j] * t) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Multiplication Random" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
            }
        }

        Matrix mat2 = Matrix(mat1);
        float t = drand48();
        mat1 *= t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat2.m[i][j] * t) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Division Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        float t = 5.0f;
        mat1 /= t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat2.m[i][j] / t) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Division Random" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
            }
        }

        Matrix mat2 = Matrix(mat1);
        float t = drand48();
        mat1 /= t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat2.m[i][j] / t) == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Matrix Multiplication Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = Matrix(mat1);
        mat1 *= mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    sum += mat3.m[i][k] * mat2.m[k][j];
                }
                REQUIRE(sum == Approx(mat1.m[i][j]));
            }
        }
    }

    SECTION( "Matrix Multiplication Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = Matrix(mat1);
        mat1 *= mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    sum += mat3.m[i][k] * mat2.m[k][j];
                }
                REQUIRE(sum == Approx(mat1.m[i][j]));
            }
        }
    }
}

TEST_CASE( "New Matrix Binary Operations", "[matrix]" )
{
    SECTION( "Addition Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = mat1 + mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] + mat2.m[i][j]) == Approx(mat3.m[i][j]));
            }
        }
    }

    SECTION( "Addition Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = mat1 + mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] + mat2.m[i][j]) == Approx(mat3.m[i][j]));
            }
        }
    }

    SECTION( "Subtraction Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = mat1 - mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] - mat2.m[i][j]) == Approx(mat3.m[i][j]));
            }
        }
    }

    SECTION( "Subtraction Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = mat1 - mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] - mat2.m[i][j]) == Approx(mat3.m[i][j]));
            }
        }
    }


    SECTION( "Scalar Multiplication Sanity" )
    {
        Matrix mat1 = identity();
        float t = 5.0f;
        Matrix mat2 = mat1 * t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] * t) == Approx(mat2.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Multiplication Random" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
            }
        }

        float t = drand48();
        Matrix mat2 = mat1 * t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] * t) == Approx(mat2.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Division Sanity" )
    {
        Matrix mat1 = identity();
        float t = 5.0f;
        Matrix mat2 = mat1 / t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] / t) == Approx(mat2.m[i][j]));
            }
        }
    }

    SECTION( "Scalar Division Random" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
            }
        }

        float t = drand48();
        Matrix mat2 = mat1 / t;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE((mat1.m[i][j] / t) == Approx(mat2.m[i][j]));
            }
        }
    }

    SECTION( "Matrix Multiplication Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();
        Matrix mat3 = mat1 * mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    sum += mat1.m[i][k] * mat2.m[k][j];
                }
                REQUIRE(sum == Approx(mat3.m[i][j]));
            }
        }
    }

    SECTION( "Matrix Multiplication Random" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
                mat2.m[i][j] = drand48();
            }
        }

        Matrix mat3 = mat1 * mat2;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    sum += mat1.m[i][k] * mat2.m[k][j];
                }
                REQUIRE(sum == Approx(mat3.m[i][j]));
            }
        }
    }
}

TEST_CASE( "Vector Transformations", "[matrix]" )
{
    SECTION( "Point Transform Sanity" )
    {
        Vec3 vec = Vec3(1.0f,1.0f,1.0f);
        Matrix mat = identity();
        Vec3 ret1 = loc_transform(mat, vec);
        Vec3 ret2;
        float temp;

        ret2[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2] + mat.m[0][3];
        ret2[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2] + mat.m[1][3];
        ret2[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2] + mat.m[2][3];
        temp = vec[0]*mat.m[3][0] + vec[1]*mat.m[3][1] + vec[2]*mat.m[3][2] + mat.m[3][3];
        ret2 /= temp;

        REQUIRE(ret1.x() == Approx(ret2.x()));
        REQUIRE(ret1.y() == Approx(ret2.y()));
        REQUIRE(ret1.z() == Approx(ret2.z()));
    }

    SECTION( "Point Transform Random" )
    {
        Vec3 vec = Vec3(drand48(),drand48(),drand48());
        Matrix mat = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat.m[i][j] = drand48();
            }
        }

        Vec3 ret1 = loc_transform(mat, vec);
        Vec3 ret2;
        float temp;

        ret2[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2] + mat.m[0][3];
        ret2[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2] + mat.m[1][3];
        ret2[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2] + mat.m[2][3];
        temp = vec[0]*mat.m[3][0] + vec[1]*mat.m[3][1] + vec[2]*mat.m[3][2] + mat.m[3][3];
        ret2 /= temp;

        REQUIRE(ret1.x() == Approx(ret2.x()));
        REQUIRE(ret1.y() == Approx(ret2.y()));
        REQUIRE(ret1.z() == Approx(ret2.z()));
    }

    SECTION( "Vector Transform Sanity" )
    {
        Vec3 vec = Vec3(1.0f,1.0f,1.0f);
        Matrix mat = identity();
        Vec3 ret1 = vec_transform(mat, vec);
        Vec3 ret2;

        ret2[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2];
        ret2[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2];
        ret2[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2];

        REQUIRE(ret1.x() == Approx(ret2.x()));
        REQUIRE(ret1.y() == Approx(ret2.y()));
        REQUIRE(ret1.z() == Approx(ret2.z()));
    }

    SECTION( "Vector Transform Random" )
    {
        Vec3 vec = Vec3(drand48(),drand48(),drand48());
        Matrix mat = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat.m[i][j] = drand48();
            }
        }

        Vec3 ret1 = vec_transform(mat, vec);
        Vec3 ret2;

        ret2[0] = vec[0]*mat.m[0][0] + vec[1]*mat.m[0][1] + vec[2]*mat.m[0][2];
        ret2[1] = vec[0]*mat.m[1][0] + vec[1]*mat.m[1][1] + vec[2]*mat.m[1][2];
        ret2[2] = vec[0]*mat.m[2][0] + vec[1]*mat.m[2][1] + vec[2]*mat.m[2][2];

        REQUIRE(ret1.x() == Approx(ret2.x()));
        REQUIRE(ret1.y() == Approx(ret2.y()));
        REQUIRE(ret1.z() == Approx(ret2.z()));
    }
}



TEST_CASE( "Determinant", "[matrix]" )
{
    SECTION( "Sanity" )
    {
        Matrix mat1 = identity();
        REQUIRE(mat1.determinant() == Approx(1.0f));
    }

    SECTION( "Random" )
    {
        Matrix mat1 = identity();
        float n[4][4] = {0.5279f, 0.6194f, 0.1917f, 0.7517f,
                         0.4135f, 0.0994f, 0.2386f, 0.2590f,
                         0.2422f, 0.7673f, 0.9237f, 0.9549f,
                         0.8713f, 0.9461f, 0.3503f, 0.4904f};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = n[i][j];
            }
        }

        REQUIRE(mat1.determinant() == Approx(0.1327194779185709f));
    }
}

TEST_CASE( "Transpose", "[matrix]" )
{
    SECTION( "Sanity" )
    {
        Matrix mat1 = identity();
        Matrix mat2 = Matrix(mat1);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == mat2.m[j][i]);
            }
        }

    }

    SECTION( "Random" )
    {
        Matrix mat1 = identity();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = drand48();
            }
        }

        Matrix mat2 = Matrix(mat1);
        mat1.transpose();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[j][i]));
            }
        }
    }
}

TEST_CASE( "Inverse", "[matrix]" )
{
    SECTION( "Sanity" )
    {
        Matrix mat1 = identity();
        mat1.inverse();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    REQUIRE(mat1.m[i][j] == Approx(1.0f));
                }
                else
                {
                    REQUIRE(mat1.m[i][j] == Approx(0.0f));
                }
            }
        }

        REQUIRE(mat1.determinant() == Approx(1.0f));

    }

    SECTION( "Random" )
    {
        Matrix mat1 = identity();
        float n1[4][4] = {0.5279f, 0.6194f, 0.1917f, 0.7517f,
                          0.4135f, 0.0994f, 0.2386f, 0.2590f,
                          0.2422f, 0.7673f, 0.9237f, 0.9549f,
                          0.8713f, 0.9461f, 0.3503f, 0.4904f};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat1.m[i][j] = n1[i][j];
            }
        }

        Matrix mat2 = identity();
        float n2[4][4] = {-0.14447f, 2.113f, -0.6752f, 0.4201f,
                          -0.2463f, -2.5764f, 0.2195f, 1.3109f,
                          -1.9657f, 1.2568f, 1.0513f, 0.3023f,
                          2.1361f, 0.3185f, 0.0252f, -1.4524f};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat2.m[i][j] = n2[i][j];
            }
        }

        mat1.inverse();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(mat1.m[i][j] == Approx(mat2.m[i][j]).margin(0.0001f));
            }
        }
    }
}
