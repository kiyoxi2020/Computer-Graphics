#include<iostream>
#include<Eigen/Eigen>
#include<opencv2/opencv.hpp>
#include"rasterization.hpp"
#include"utility.hpp"
#include"camera.hpp"

int main(){
    // define rasterizor
    int width = 500;
    int height = 500;
    rasterizor r(width, height);
    // define camera position, gaze direction and up direction
    Eigen::Vector3f pos = {0, 0, 5};
    Eigen::Vector3f up = {0, 1, 0};
    Eigen::Vector3f gaze = {0, 0, -1};
    camera c(pos, up, gaze);
    // define imaging region
    float eye_fov = 45;  // unit: degree
    float aspect = 1;   // height(y)/width(x)
    float zNear = 0.1;  // near imaging plane
    float zFar = 50;    // far imaging plane

    // define rotation angle and axis of the model
    float angle = 0;    // unit: degree
    char axis = 'z';

    // define the vertices and colors of traingles
    std::vector<Eigen::Vector3f> vertices
        {
            {2.0,0.0,-2.0}, 
            {0.0,2.0,-2.0}, 
            {-2.0,0.0,-2.0},
            {3.5, -1, -5},
            {2.5, 1.5, -5},
            {-1, 0.5, -5}
        };
    std::vector<Eigen::Vector3f> ind
        {
            {0, 1, 2},
            {3, 4, 5}
        };
    std::vector<Eigen::Vector3f> colors
        {
            {255.0, 0.0, 0.0},
            {0.0, 0.0, 255.0},
            {0.0, 255.0, 0.0},
            {185.0, 217.0, 238.0},
            {185.0, 217.0, 238.0},
            {185.0, 217.0, 238.0}
        };
    r.load_pos(vertices);
    r.load_ind(ind);
    r.load_colors(colors);

    int key = 0;
    while (key != 27) {
        r.clear();
        // MVP transform: model, view, projection
        r.set_model(get_model_matrix(angle, axis));
        r.set_view(get_view_matrix(c));
        r.set_projection(get_project_matrix(eye_fov, aspect, zNear, zFar));
        // rendering
        r.draw();

        // show rendered image and save
        cv::Mat image(height, width, CV_32FC3, r.get_frame_buf().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imwrite("output.png",image);
        cv::imshow("image", image);
        key = cv::waitKey(10);
        // angle += 1;
        if(key=='a')
            angle+=10;
        else if(key=='d')
            angle-=10;

    }
    std::cout<<"Triangle rasterization done!"<<std::endl;
    return 0;
}