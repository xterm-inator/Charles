#include "Camera.h"
#include "Image.h"
#include <thread>
#include <chrono>
#include <opencv2/videoio.hpp>
#include <jetson-utils/logging.h>
#include <opencv2/imgcodecs.hpp>
//#include <jetson-utils/videoSource.h>

Camera::Camera()
{
//    Source = videoSource::Create("csi://0");
    Source = cv::VideoCapture("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
}

bool Camera::Setup()
{
//    Source.open();

    if (!Source.isOpened()) {
        LogError("Unable to open camera\n");
    }

//    Source.set(cv::CAP_PROP_FPS, 30);
//    Source.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
//    Source.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);

    // wait 3 seconds for the camera to warm up
    std::this_thread::sleep_for (std::chrono::seconds(3));

    return true;
}

int Camera::Capture(Image& NewImage)
{
    NewImage.SetDimensions(HEIGHT, WIDTH);

    return Source.read(NewImage.RawImage);

//    LogVerbose("width: %d, height: %d \n", Source->GetWidth(), Source->GetHeight());
}
