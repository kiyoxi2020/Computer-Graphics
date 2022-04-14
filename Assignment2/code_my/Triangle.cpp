#include"Triangle.hpp"

void triangle::set_v(int ind, Vector3f v0){
    v[ind] = v0;
}

void triangle::set_color(int ind, Vector3f c){
    color[ind] = c;
}

bool triangle::insideTriangle(float x, float y){
    bool t1;
    for(int i=0;i<3;i++){
        Vector3f v0 = {float(x), float(y), 0};
        Vector3f v1 = {v[i].x(), v[i].y(), 0};
        int j = (i+1)<3?i+1:0;
        Vector3f v2 = {v[j].x(), v[j].y(), 0};
        Vector3f a = v0 - v1;
        Vector3f b = v2 - v1;
        Vector3f x0 = a.cross(b);
        bool t2 = (x0[2]>0);
        if(i==0) t1 = t2;
        else if(t1!=t2)
            return false;
    }
    return true;
}

Vector3f triangle::interp_coef(float x, float y){
    // Barycentric coordinate
    Vector2f A = {v[0].x(), v[0].y()};
    Vector2f B = {v[1].x(), v[1].y()};
    Vector2f C = {v[2].x(), v[2].y()};
    Vector3f out;
    float alpha = (-(x-B.x())*(C.y()-B.y()) + (y-B.y())*(C.x()-B.x()))/
                (-(A.x()-B.x())*(C.y()-B.y())+(A.y()-B.y())*(C.x()-B.x()));
    float beta = (-(x-C.x())*(A.y()-C.y())+(y-C.y())*(A.x()-C.x()))/
                (-(B.x()-C.x())*(A.y()-C.y())+(B.y()-C.y())*(A.x()-C.x()));
    float gamma = 1-alpha-beta;
    out << alpha, beta, gamma;
    return out;
}

