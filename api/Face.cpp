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
