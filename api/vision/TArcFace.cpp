//
// Created by David on 9/07/2023.
//

#include "TArcFace.h"

TArcFace::TArcFace()
{
    FaceNet.opt.use_vulkan_compute = true;
    FaceNet.load_param("../vision/models/mobilefacenet/mobilefacenet.param");
    FaceNet.load_model("../vision/models/mobilefacenet/mobilefacenet.bin");
}

TArcFace::~TArcFace()
{
    FaceNet.clear();
}

cv::Mat TArcFace::GetFeature(const cv::Mat& Image)
{
    std::vector<float> Feature;

    ncnn::Mat Input = ncnn::Mat::from_pixels(Image.data, ncnn::Mat::PIXEL_BGR, Image.cols, Image.rows);

    ncnn::Extractor Extractor = FaceNet.create_extractor();
    Extractor.set_light_mode(true);
    Extractor.input("data", Input);

    ncnn::Mat Output;
    Extractor.extract("fc1", Output);

    Feature.resize(FeatureDimension);

    for(int i = 0; i < FeatureDimension; i++)
    {
        Feature[i] = Output[i];
    }

    cv::Mat Result = cv::Mat(Feature, true);

    return ZScore(Result);
}

cv::Mat TArcFace::ZScore(const cv::Mat& Feature)
{
    cv::Mat Mean, Standard;
    cv::meanStdDev(Feature, Mean, Standard);
    return ((Feature - Mean) / Standard);
}
