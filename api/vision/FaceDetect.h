#pragma once

#include <vector>
#include <jetson-inference/detectNet.h>
#include "Face.h"
#include "TRetina.h"
#include "TArcFace.h"
#include "TWarp.h"

class Image;

class FaceDetect
{
public:
    FaceDetect();
    int Detect(Image& ImageToCheck);
    std::vector<Face> Faces;

private:
    TRetina Retina{1280, 720};
    TArcFace ArcFace{};
    TWarp Warp{};
//    detectNet* Net;
//    const unsigned int OverlayFlags = detectNet::OverlayFlagsFromStr("");
};

