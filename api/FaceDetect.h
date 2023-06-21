#pragma once

#include <vector>
#include <jetson-inference/detectNet.h>
#include "Face.h"
#include "TRetina.h"

class Image;

class FaceDetect
{
public:
    FaceDetect();
    int Detect(Image& ImageToCheck);
    std::vector<Face> Faces;

private:
    TRetina Net{3280, 2464};
//    detectNet* Net;
//    const unsigned int OverlayFlags = detectNet::OverlayFlagsFromStr("");
};

