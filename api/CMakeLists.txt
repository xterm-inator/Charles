cmake_minimum_required(VERSION 3.10)
project(charles)

#set(ncnn_DIR /home/charles/ncnn/build/install/lib/cmake/ncnn)
set(glslang_DIR /home/charles/glslang/build/install/lib/cmake/glslang)
set(SPIRV-Tools-opt_DIR /home/charles/glslang/build/install/lib/cmake/SPIRV-Tools-opt)
set(SPIRV-Tools_DIR /home/charles/glslang/build/install/lib/cmake/SPIRV-Tools)

find_package(PkgConfig)
find_package(jetson-utils REQUIRED)
find_package(jetson-inference REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)
find_package(OpenMP REQUIRED)
find_package(SPIRV-Tools REQUIRED)
find_package(SPIRV-Tools-opt REQUIRED)
find_package(glslang CONFIG REQUIRED)
find_package(ncnn REQUIRED)
find_package(Threads REQUIRED)


pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)
pkg_check_modules(GST_WEBRTC REQUIRED gstreamer-webrtc-1.0)

#FIND_GSTREAMER_COMPONENT(GSTREAMER_WEBRTC gstreamer-webrtc-1.0 gst/webrtc/webrtc.h gstwebrtc-1.0)

set(CMAKE_CXX_STANDARD 17)

link_directories(
        /usr/lib/aarch64-linux-gnu/tegra
        ${GSTREAMER_LIBRARY_DIRS}
)

cuda_add_executable(${PROJECT_NAME} main.cpp Camera.cpp Camera.h Image.cpp Image.h FaceDetect.cpp FaceDetect.h Face.cpp Face.h TRetina.cpp TRetina.h)

include_directories(
        ${jetson-inference_INCLUDE_DIRS}
        ${jetson-utils_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CUDA_STANDARD_INCLUDE_DIRECTORIES}
        ${ncnn_INCLUDE_DIRECTORIES}
        ${GSTREAMER_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}
        jetson-inference
        jetson-utils
        OpenMP::OpenMP_CXX
        ncnn
        ${GSTREAMER_LIBRARIES}
        ${GST_APP_LIBRARIES}
        ${GST_VIDEO_LIBRARIES}
        ${GST_WEBRTC_LIBRARIES}
#        glslang::glslang
#        glslang::SPIRV
#        glslang::glslang-default-resource-limits
)

