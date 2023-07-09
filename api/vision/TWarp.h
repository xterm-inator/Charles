#pragma once

#include "TRetina.h"
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Face;

class TWarp {
public:
    TWarp() = default;
    ~TWarp() = default;

    cv::Mat Process(cv::Mat& SmallFrame, Face& Face);

private:
    double Angle;

    static int MatrixRank(cv::Mat M);
    static cv::Mat VarAxis0(const cv::Mat& Src);
    static cv::Mat MeanAxis0(const cv::Mat& Src);
    static cv::Mat ElementwiseMinus(const cv::Mat& A,const cv::Mat& B);
    static cv::Mat SimilarTransform(cv::Mat Src,cv::Mat Dst);

public:
    [[nodiscard]] inline double GetAngle() const { return Angle; };
};
