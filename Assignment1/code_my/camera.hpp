#pragma once

#include<Eigen/Eigen>

class camera{
    public:
        Eigen::Vector3f pos;
        Eigen::Vector3f up;
        Eigen::Vector3f gaze;

        camera(Eigen::Vector3f p, Eigen::Vector3f u, Eigen::Vector3f g):
            pos(p), up(u), gaze(g){};
};

