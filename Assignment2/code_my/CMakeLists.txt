cmake_minimum_required(VERSION 3.0)
project(rasterization)

include_directories("C:/Program Files (x86)/Eigen3/include/eigen3")
include_directories("F:/opencv-4.5.5/build/install/include")
link_directories("F:/opencv-4.5.5/build/install/x64/mingw/lib")

add_executable(rasterization main.cpp rasterization.hpp rasterization.cpp utility.hpp camera.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(rasterization libopencv_core455.dll.a libopencv_highgui455.dll.a libopencv_imgproc455.dll.a libopencv_imgcodecs455.dll.a)
