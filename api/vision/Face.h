#pragma once

#include <opencv4/opencv2/core/types.hpp>
#include <jetson-inference/detectNet.h>
#include <opencv2/core/mat.hpp>

class Face
{
public:
    explicit Face(detectNet::Detection Detection);
    explicit Face();

    cv::Rect_<float> BoundingBox;
    cv::Point2f Landmarks[5];
    cv::Point2f FaceImageLandmarks[5];
    float FaceProb{0};
    cv::Mat FaceImage;
    double Angle{0};

    void GenerateFaceImage(const cv::Mat& Image);
public:
    inline cv::Rect_<float> GetBoundingBox() { return BoundingBox; }
};
