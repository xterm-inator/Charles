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

    LogVerbose("faces: %d\n", result);

    if (result > 0)
    {
        for (Face& Face : Faces) {
            ImageToCheck.DrawFace(&Face);
            ImageToCheck.DrawLandmarks(&Face);
        }

        ImageToCheck.SaveImage("/home/charles/test_image.jpg");
    }

    return result;
}
