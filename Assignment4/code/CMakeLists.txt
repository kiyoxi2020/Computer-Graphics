cmake_minimum_required(VERSION 3.10)
project(BezierCurve)

include_directories("C:/Program Files (x86)/Eigen3/include/eigen3")
include_directories("F:/opencv-4.5.5/build/install/include")
link_directories("F:/opencv-4.5.5/build/install/x64/mingw/lib")

set(CMAKE_CXX_STANDARD 14)

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve libopencv_core455.dll.a libopencv_highgui455.dll.a libopencv_imgproc455.dll.a libopencv_imgcodecs455.dll.a)