#pragma once
#include<Eigen/Eigen>
#include"camera.hpp"

const float PI = 3.1415926;

Eigen::Matrix4f get_model_matrix(float angle, char axis){
    angle = angle / 180. * PI;
    Eigen::Matrix4f model;
    if(axis=='x'){
        model << 1, 0, 0, 0, 
                 0, cos(angle), -sin(angle), 0,
                 0, sin(angle), cos(angle), 0,
                 0, 0, 0, 1;

    }
    else if(axis=='y'){
        model << cos(angle), 0, sin(angle), 0,
                 0, 1, 0, 0,
                 -sin(angle), 0, cos(angle), 0,
                 0, 0, 0, 1;
    }
    else if(axis=='z'){
        model << cos(angle), -sin(angle), 0, 0,
                 sin(angle), cos(angle), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1;
    }
    return model;
}

Eigen::Matrix4f get_view_matrix(camera c){
    Eigen::Matrix4f v;
    Eigen::Matrix4f t;
    Eigen::Matrix4f r;
    t << 1, 0, 0, -c.pos.x(),
         0, 1, 0, -c.pos.y(),
         0, 0, 1, -c.pos.z(),
         0, 0, 0, 1;
    Eigen::Vector3f gt = c.gaze.cross(c.up);
    r << gt.x(), gt.y(), gt.z(), 0, 
         c.up.x(), c.up.y(), c.up.z(), 0,
         -c.gaze.x(), -c.gaze.y(), -c.gaze.z(), 0,
         0, 0, 0, 1;
    v = t * r;
    return v;
}

Eigen::Matrix4f get_project_matrix(float eye_fov, float aspect, float zNear, float zFar){
    Eigen::Matrix4f p;
    Eigen::Matrix4f pToO;
    Eigen::Matrix4f O;
    eye_fov = eye_fov / 180. * PI;
    float n = -zNear;  // near
    float f = -zFar;   // far
    float t = zNear * tan(eye_fov/2);  // top
    float b = -t;  // bottom
    float r = t * aspect;  // right
    float l = -r;  // left
    pToO << n, 0, 0, 0,
            0, n, 0, 0,
            0, 0, n+f, -n*f,
            0, 0, 1, 0;
    Eigen::Matrix4f O1;
    O1 << 2/(r-l), 0, 0, 0,
          0, 2/(t-b), 0, 0,
          0, 0, 2/(n-f), 0,
          0, 0, 0, 1;
    Eigen::Matrix4f O2;
    O2 << 1, 0, 0, -(r+l)/2,
          0, 1, 0, -(t+b)/2,
          0, 0, 1, -(n+f)/2,
          0, 0, 0, 1;
    O = O1 * O2;
    p = O * pToO;
    return p;
}