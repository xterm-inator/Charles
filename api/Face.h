#pragma once

#include <opencv4/opencv2/core/types.hpp>
#include <jetson-inference/detectNet.h>

class Face
{
public:
    explicit Face(detectNet::Detection Detection);
    explicit Face();

    cv::Rect_<float> BoundingBox;
    cv::Point2f Landmarks[5];
    float FaceProb{0};

public:
    inline cv::Rect_<float> GetBoundingBox() { return BoundingBox; }
};
