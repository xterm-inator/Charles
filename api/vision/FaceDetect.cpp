#include <trantor/utils/Logger.h>
#include <opencv2/imgcodecs.hpp>
#include <drogon/HttpAppFramework.h>
#include "FaceDetect.h"
#include "Image.h"
#include "Face.h"
#include "plugins/People.h"

FaceDetect::FaceDetect()
{
//    Net = detectNet::Create("facedetect");
}

int FaceDetect::Detect(Image& ImageToCheck)
{
    Faces.clear();

    int result = Retina.DetectFace(ImageToCheck, Faces);

//    LOG_INFO << "faces: " << result;

    if (result > 0)
    {
        auto* PeoplePtr = drogon::app().getPlugin<People>();

        for (Face& Face : Faces) {
            Face.GenerateFaceImage(ImageToCheck.RawImage);

            cv::Mat Aligned = Warp.Process(Face.FaceImage, Face);

            Face.Angle = Warp.GetAngle();

            cv::Mat FaceFeature = ArcFace.GetFeature(Aligned);

            ImageToCheck.DrawFace(&Face);
            ImageToCheck.DrawLandmarks(&Face);
        }

//        ImageToCheck.SaveImage("/home/charles/test_image.jpg");
    }

    ImageToCheck.CurrentImage = ImageToCheck.RawImage.clone();

    return result;
}
