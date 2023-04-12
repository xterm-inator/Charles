cmake_minimum_required(VERSION 3.10)
project(charles)

find_package(jetson-utils REQUIRED)
find_package(jetson-inference REQUIRED)
find_package(OpenCV REQUIRED core imgproc)
find_package(CUDA REQUIRED)

set(CMAKE_CXX_STANDARD 20)

link_directories(/usr/lib/aarch64-linux-gnu/tegra)

cuda_add_executable(${PROJECT_NAME} main.cpp Camera.cpp Camera.h Image.cpp Image.h)

include_directories(
        ${jetson-inference_INCLUDE_DIRS}
        ${jetson-utils_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CUDA_STANDARD_INCLUDE_DIRECTORIES}
)

target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}
        jetson-inference
        jetson-utils
)
