#include "Renderer.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include "global.hpp"
#include <chrono>
#include <opencv2/opencv.hpp>

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main(int argc, char** argv)
{
    Scene scene(1280, 960);

    MeshTriangle bunny("../models/bunny/bunny.obj");

    scene.Add(&bunny);
    scene.Add(std::make_unique<Light>(Vector3f(-20, 70, 20), 1));
    scene.Add(std::make_unique<Light>(Vector3f(20, 70, 20), 1));
    // scene.Add(std::make_unique<Light>(Vector3f(0, 70, 20), 1));
    scene.buildBVH();

    Renderer r;

    auto start = std::chrono::system_clock::now();
    std::vector<Vector3f> framebuffer = r.Render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nRender complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";


    for (auto i = 0; i < scene.height * scene.width; ++i) {
         framebuffer[i].x = 255 * clamp(0, 1, framebuffer[i].x);
         framebuffer[i].y = 255 * clamp(0, 1, framebuffer[i].y);
         framebuffer[i].z = 255 * clamp(0, 1, framebuffer[i].z);
    }
    cv::Mat image(scene.height,  scene.width, CV_32FC3, framebuffer.data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    cv::imwrite("output.png", image);
    return 0;
}