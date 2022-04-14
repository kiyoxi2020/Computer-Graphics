#pragma once
#include<Eigen\Eigen>
#include"Triangle.hpp"
#include<iostream>
using namespace Eigen;


class rasterizor{
    public:
        rasterizor(int w, int h): width(w), height(h){ frame_buf.resize(w*h); }
        void load_pos(std::vector<Vector3f> pos);
        void load_ind(std::vector<Vector3f> ind);
        void set_model(Matrix4f m){ model=m; }
        void set_view(Matrix4f v){ view=v; }
        void set_projection(Matrix4f p){ projection=p; }
        void draw();
        void render(triangle t);
        void drawLine(Vector3f v1, Vector3f v2, Vector3f c1, Vector3f c2);
        void clear(){ std::fill(frame_buf.begin(), frame_buf.end(), Vector3f{0, 0, 0});}
        std::vector<Vector3f>& get_frame_buf(){ return frame_buf; }
        void set_pixel(int x, int y, Vector3f color);

    private:
        // mvp transform matrix
        Matrix4f model;
        Matrix4f view;
        Matrix4f projection;

        // frame buffer
        int width, height;
        std::vector<Vector3f> frame_buf;

        // vertices
        std::vector<Vector3f> pos_buf;
        std::vector<Vector3f> pos_ind;

};

