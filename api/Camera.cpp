#include "Camera.h"
#include "Image.h"
#include <thread>
#include <chrono>
#include <jetson-utils/videoSource.h>

Camera::Camera()
{
    Source = videoSource::Create("csi://0");
}

bool Camera::Setup()
{
    bool result = Source->Open();

    // wait 3 seconds for the camera to warm up
    std::this_thread::sleep_for (std::chrono::seconds(3));

    return result;
}

int Camera::Capture(Image& NewImage)
{
    int Status = 0;
    uchar3* Image = NewImage.GetRawImage();

    Source->Capture(&Image, &Status);
    return Status;
}

unsigned int Camera::GetImageSize()
{
    return 0;
}
