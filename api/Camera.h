#pragma once

#include <opencv2/videoio.hpp>

#define WIDTH 1280
#define HEIGHT 720

//#define WIDTH 3280
//#define HEIGHT 2464

class Image;

class Camera
{
public:
    Camera();
    bool Setup();
    int Capture(Image& NewImage);
private:
    cv::VideoCapture Source{};

};
