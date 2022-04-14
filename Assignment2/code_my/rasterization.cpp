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

void rasterizor::load_colors(std::vector<Vector3f> colors){
    color_buf = colors;
}

rasterizor::rasterizor(int w, int h): width(w), height(h){ 
    frame_buf.resize(w*h);
    z_buf.resize(w*h);
}

void rasterizor::draw(){
    Matrix4f mvp = projection * view * model;
    // std::cout<<mvp<<std::endl;
    for(auto& i : pos_ind){
        // define triangle
        triangle t;
        // obtain the vertices and colors of triangle
        Vector4f v[3]={ 
            to_vec4(pos_buf[i[0]], 1),
            to_vec4(pos_buf[i[1]], 1),
            to_vec4(pos_buf[i[2]], 1)
        };
        Vector3f c[3]={
            color_buf[i[0]],
            color_buf[i[1]],
            color_buf[i[2]]
        };

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
            t.set_color(j, c[j]);
        }
        render(t);
    }
}

void rasterizor::render(triangle t){
    int xmin = std::min(t.a().x(), std::min(t.b().x(), t.c().x()));
    int xmax = std::max(t.a().x(), std::max(t.b().x(), t.c().x()));
    int ymin = std::min(t.a().y(), std::min(t.b().y(), t.c().y()));
    int ymax = std::max(t.a().y(), std::max(t.b().y(), t.c().y()));

    for(int x=xmin; x<=xmax; x++){
        for(int y=ymin; y<=ymax; y++){
            if(t.insideTriangle(x,y)){
                Vector3f coef = t.interp_coef(x,y);
                float depth = t.v[0].z()*coef[0]+t.v[1].z()*coef[1]+t.v[2].z()*coef[2];
                int ind = get_ind(x,y);
                if(depth>z_buf[ind]){
                    Vector3f color = t.color[0]*coef[0]+t.color[1]*coef[1]+t.color[2]*coef[2];
                    set_pixel(x, y, color);
                    z_buf[ind] = depth;
                }
            }
        }
    }
}

void rasterizor::set_pixel(int x, int y, Vector3f color){
    if(x>=0 && x<width && y>=0 && y<height){
        int ind = get_ind(x, y);
        frame_buf[ind] = color;
    }
}

int rasterizor::get_ind(int x, int y){
    return (height-y-1)*width+x;
}

void rasterizor::clear(){ 
    std::fill(frame_buf.begin(), frame_buf.end(), Vector3f{0, 0, 0});
    std::fill(z_buf.begin(), z_buf.end(), -std::numeric_limits<float>::max());
}