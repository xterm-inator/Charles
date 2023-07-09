//
// Created by David on 9/07/2023.
//

#pragma once

#include <cmath>
#include <vector>
#include <string>
#include "net.h"
#include <opencv2/highgui.hpp>

class TArcFace {
public:
    TArcFace();
    ~TArcFace();

    cv::Mat GetFeature(const cv::Mat& Image);

private:
    ncnn::Net FaceNet;
    const int FeatureDimension{128};

    /**
     *    This is a normalize function before calculating the cosine distance. Experiment has proven it can destory the
     *    original distribution in order to make two feature more distinguishable.
     *    mean value is set to 0 and std is set to 1
     */
    static cv::Mat ZScore(const cv::Mat& Feature);
};
