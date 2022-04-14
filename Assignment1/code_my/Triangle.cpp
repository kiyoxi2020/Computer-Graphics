#include"Triangle.hpp"

void triangle::set_v(int ind, Vector3f v0){
    v[ind] = v0;
}

void triangle::set_color(int ind, Vector3f c){
    color[ind] = c;
}
