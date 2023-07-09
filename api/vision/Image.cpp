#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "Image.h"
#include "Face.h"

Image::Image() = default;

void Image::DrawFace(Face* Face)
{
    cv::rectangle(RawImage, Face->BoundingBox, cv::Scalar(0, 255, 0));
}

void Image::DrawLandmarks(Face *Face)
{
    cv::circle(RawImage, Face->Landmarks[0], 2, cv::Scalar(0, 255, 255), -1);
    cv::circle(RawImage, Face->Landmarks[1], 2, cv::Scalar(0, 255, 255), -1);
    cv::circle(RawImage, Face->Landmarks[2], 2, cv::Scalar(0, 255, 255), -1);
    cv::circle(RawImage, Face->Landmarks[3], 2, cv::Scalar(0, 255, 255), -1);
    cv::circle(RawImage, Face->Landmarks[4], 2, cv::Scalar(0, 255, 255), -1);
}

void Image::SaveImage(const char* Filename)
{
    cv::imwrite(Filename, RawImage);
}