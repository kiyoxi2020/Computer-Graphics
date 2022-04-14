#pragma once
#include<Eigen\Eigen>
#include"Triangle.hpp"
#include<iostream>
using namespace Eigen;


class rasterizor{
    public:
        rasterizor(int w, int h);
        void load_pos(std::vector<Vector3f> pos);
        void load_ind(std::vector<Vector3f> ind);
        void load_colors(std::vector<Vector3f> colors);
        void set_model(Matrix4f m){ model=m; }
        void set_view(Matrix4f v){ view=v; }
        void set_projection(Matrix4f p){ projection=p; }
        void draw();
        void render(triangle t);
        void drawLine(Vector3f v1, Vector3f v2, Vector3f c1, Vector3f c2);
        void clear();
        std::vector<Vector3f>& get_frame_buf(){ return frame_buf; }
        void set_pixel(int x, int y, Vector3f color);
        int get_ind(int x, int y);

    private:
        // mvp transform matrix
        Matrix4f model;
        Matrix4f view;
        Matrix4f projection;

        // frame buffer
        int width, height;
        std::vector<Vector3f> frame_buf;
        std::vector<float> z_buf;

        // vertices
        std::vector<Vector3f> pos_buf;
        std::vector<Vector3f> pos_ind;
        std::vector<Vector3f> color_buf;

};

