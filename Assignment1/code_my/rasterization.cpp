#include"rasterization.hpp"

auto to_vec4(Vector3f v3, float w=1.0f){
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

void rasterizor::load_pos(std::vector<Vector3f> pos){
    pos_buf = pos;
}

void rasterizor::load_ind(std::vector<Vector3f> ind){
    pos_ind = ind;
}

void rasterizor::draw(){
    Matrix4f mvp = projection * view * model;
    // std::cout<<mvp<<std::endl;
    Vector3f colors[3]={{255.0,0.0,0.0}, 
                        {0.0,255.0,0.0}, 
                        {0.0,0.0,255.0}};
    for(auto& i : pos_ind){
        // define triangle
        triangle t;
        // obtain the vertices of triangle
        Vector4f v[3]={ 
            to_vec4(pos_buf[i[0]], 1),
            to_vec4(pos_buf[i[1]], 1),
            to_vec4(pos_buf[i[2]], 1)};

        // mvp transform
        for(auto& v0 : v){
            v0 = mvp * v0;
            v0 /= v0.w();
            v0.x() = (v0.x() / 2.0 + 0.5) * width;
            v0.y() = (v0.y() / 2.0 + 0.5) * height;
        }

        // set the vertices and colors of the triangle
        for(int j=0;j<3;j++){
            t.set_v(j, v[j].head<3>());
            t.set_color(j, colors[j]);
        }
        render(t);
    }
}

void rasterizor::render(triangle t){
    drawLine(t.a(), t.b(), t.ac(), t.bc());
    drawLine(t.b(), t.c(), t.bc(), t.cc());
    drawLine(t.c(), t.a(), t.cc(), t.ac());
}

void rasterizor::drawLine(Vector3f v1, Vector3f v2, Vector3f c1, Vector3f c2){
    for(int i=int(v1.x());i!=int(v2.x());i=i+int((v2.x()-v1.x())/abs(v2.x()-v1.x()))){
        int x0 = i;
        float gamma = (x0 - v1.x())/(v2.x()-v1.x());
        int y0 = v1.y() + (v2.y()-v1.y()) * gamma;
        set_pixel(x0, y0, c1*(1-gamma) + c2*gamma);
    }
    for(int i=int(v1.y());i!=int(v2.y());i=i+int((v2.y()-v1.y())/abs(v2.y()-v1.y()))){
        int y0 = i;
        float gamma = (y0 - v1.y())/(v2.y()-v1.y());
        int x0 = v1.x() + (v2.x()-v1.x()) * gamma;
        set_pixel(x0, y0, c1*(1-gamma) + c2*gamma);
    }
}

void rasterizor::set_pixel(int x, int y, Vector3f color){
    if(x>=0 && x<width && y>=0 && y<height){
        int ind = (height-y-1)*width+x;
        frame_buf[ind] = color;
    }
}