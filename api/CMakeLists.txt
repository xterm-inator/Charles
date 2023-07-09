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
find_package(Drogon CONFIG REQUIRED)


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

#cuda_add_executable(${PROJECT_NAME} main.cpp vision/Camera.cpp vision/Camera.h vision/Image.cpp vision/Image.h vision/FaceDetect.cpp vision/FaceDetect.h vision/Face.cpp vision/Face.h vision/TRetina.cpp vision/TRetina.h)
cuda_add_executable(${PROJECT_NAME} main.cpp)

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
        Drogon::Drogon
        ${GSTREAMER_LIBRARIES}
        ${GST_APP_LIBRARIES}
        ${GST_VIDEO_LIBRARIES}
        ${GST_WEBRTC_LIBRARIES}
#        glslang::glslang
#        glslang::SPIRV
#        glslang::glslang-default-resource-limits
)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(vision VISION_SRC)
aux_source_directory(utils UTILS_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC}
               ${VISION_SRC}
               ${UTILS_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

add_subdirectory(test)