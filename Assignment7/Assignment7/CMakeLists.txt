cmake_minimum_required(VERSION 3.10)
project(RayTracing)

include_directories("F:/opencv-4.5.5/build/install/include")
link_directories("F:/opencv-4.5.5/build/install/x64/mingw/lib")
set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp Object.hpp Vector.cpp Vector.hpp Sphere.hpp global.hpp Triangle.hpp Scene.cpp
        Scene.hpp Light.hpp AreaLight.hpp BVH.cpp BVH.hpp Bounds3.hpp Ray.hpp Material.hpp Intersection.hpp
        Renderer.cpp Renderer.hpp)
target_link_libraries(RayTracing libopencv_core455.dll.a libopencv_highgui455.dll.a libopencv_imgproc455.dll.a libopencv_imgcodecs455.dll.a)
