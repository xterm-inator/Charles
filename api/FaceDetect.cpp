#include "FaceDetect.h"
#include "Image.h"
#include "Face.h"

FaceDetect::FaceDetect()
{
//    Net = detectNet::Create("facedetect");
}

int FaceDetect::Detect(Image& ImageToCheck)
{
    Faces.clear();

    int result = Net.DetectFace(ImageToCheck, Faces);

    if (result > 0)
    {
//        for (detectNet::Detection Detection : Detections)
//        {
//            if (Detection.Confidence > 0.8f)
//            {
//                Face Face(Detection);
//                Faces.push_back(Face);
//            }
//        }
    }
    LogVerbose("faces: %d\n", result);

    return result;
}

//int FaceDetect::Detect(Image& ImageToCheck)
//{
//    Faces.clear();
//
//    detectNet::Detection Detections[20];
//
//    const int result = Net->Detect(
//            ImageToCheck.RawImage,
//            ImageToCheck.GetWidth(),
//            ImageToCheck.GetHeight(),
//            Detections,
//            OverlayFlags);
//
//    if (result > 0)
//    {
//        for (detectNet::Detection Detection : Detections)
//        {
//            if (Detection.Confidence > 0.8f)
//            {
//                Face Face(Detection);
//                Faces.push_back(Face);
//            }
//        }
//    }
//
//    return result;
//}
