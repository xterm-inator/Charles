//
// Created by David on 8/07/2023.
//

#include <opencv2/imgcodecs.hpp>
#include "utils/Base64.h"
#include "Vision.h"
#include "vision/Camera.h"
#include "vision/FaceDetect.h"
#include "vision/Image.h"

void Vision::initAndStart(const Json::Value &config)
{
    LOG_INFO << "Vision plugin starting";

    ThreadHandler = std::thread(&Vision::Run, this, std::ref(ShouldRun));
}

void Vision::shutdown()
{
    LOG_INFO << "Vision plugin stopping";
    ShouldRun = false;
    ThreadHandler.join();
}

void Vision::Run(std::atomic<bool>& IsRunning)
{
    Camera Camera;
    Camera.Setup();

    FaceDetect FaceDetect;

    while (IsRunning)
    {
        if (!Camera.Capture(FrameImage))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        FaceDetect.Detect(FrameImage);

        FpsCounter.Update();

        Ready = true;
    }
}

std::string Vision::GetBase64Image() const
{
    return macaron::Base64::Encode(GetImageString());
}

std::string Vision::GetImageString() const
{
    std::vector<int> Params{cv::IMWRITE_JPEG_QUALITY, 90};

    std::vector<uchar> Buff;
    cv::imencode(".jpg", FrameImage.CurrentImage, Buff);
    return std::string{Buff.begin(), Buff.end()};
//    std::string ImageString;
//    for (uchar i: Buff)
//    {
//        ImageString += i;
//    }
//
//    return ImageString;
}
