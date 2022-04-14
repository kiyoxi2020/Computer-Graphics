#pragma once
#include<Eigen\Eigen>
using namespace Eigen;

class triangle{
    public:
        Vector3f v[3];  // vertices of the triangle
        Vector3f color[3];  // rgb color of every triangle

        triangle(){}; 
        void set_v(int ind, Vector3f v0);
        void set_color(int ind, Vector3f c);
        Vector3f a(){ return v[0]; }
        Vector3f b(){ return v[1]; }
        Vector3f c(){ return v[2]; }
        Vector3f ac(){ return color[0]; }
        Vector3f bc(){ return color[1]; }
        Vector3f cc(){ return color[2]; }
        bool insideTriangle(float x, float y);
        Vector3f interp_coef(float x, float y);
};