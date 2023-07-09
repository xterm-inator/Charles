//
// Created by David on 14/04/2023.
//

#include <opencv4/opencv2/core/types.hpp>
#include <jetson-inference/detectNet.h>
#include "Face.h"

Face::Face(detectNet::Detection Detection)
{
    BoundingBox = cv::Rect_<float>(Detection.Left, Detection.Top, Detection.Left + Detection.Right,
                                                    Detection.Top + Detection.Bottom);
}

Face::Face() = default;


void Face::GenerateFaceImage(const cv::Mat& Image)
{
    FaceImage = Image(cv::Range(BoundingBox.y, BoundingBox.y + BoundingBox.height), cv::Range(BoundingBox.x, BoundingBox.x + BoundingBox.width));

    FaceImageLandmarks[0].x = Landmarks[0].x - BoundingBox.x;
    FaceImageLandmarks[0].y = Landmarks[0].y - BoundingBox.y;
    FaceImageLandmarks[1].x = Landmarks[1].x - BoundingBox.x;
    FaceImageLandmarks[1].y = Landmarks[1].y - BoundingBox.y;
    FaceImageLandmarks[2].x = Landmarks[2].x - BoundingBox.x;
    FaceImageLandmarks[2].y = Landmarks[2].y - BoundingBox.y;
    FaceImageLandmarks[3].x = Landmarks[3].x - BoundingBox.x;
    FaceImageLandmarks[3].y = Landmarks[3].y - BoundingBox.y;
    FaceImageLandmarks[4].x = Landmarks[4].x - BoundingBox.x;
    FaceImageLandmarks[4].y = Landmarks[4].y - BoundingBox.y;
}