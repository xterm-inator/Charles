//
// Created by David on 15/04/2023.
//

#pragma once

#include <vector>
#include "net.h"
#include "Face.h"

class Image;

class TRetina {
public:
    TRetina(unsigned int Width, unsigned int Height);
    virtual ~TRetina();

    int DetectFace(Image& Image, std::vector<Face>& Faces);

private:
    ncnn::Net RetinaFace;
    unsigned int ImgWidth;
    unsigned int ImgHeight;

    float ScaleX{0.f};
    float ScaleY{0.f};

    const int RetinaWidth{320};
    const int RetinaHeight{240};

    const float ProbThreshold{0.92f};
    const float NMSThreshold{0.4f};

private:
//    static inline float IntersectionArea(const Face& a, const Face& b) { (a.BoundingBox & b.BoundingBox) };

    static void QSortDescentInplace(std::vector<Face>& Faces, int Left, int Right);
    static void QSortDescentInplace(std::vector<Face>& Faces);
    static void NMSSortedBboxes(const std::vector<Face>& Faces, std::vector<int>& Picked, float Threshold);
    static ncnn::Mat GenerateAnchors(int BaseSize, const ncnn::Mat& Ratios, const ncnn::Mat& Scales);
    void GenerateProposals(const ncnn::Mat& Anchors, int FeatStride, const ncnn::Mat& ScoreBlob, const ncnn::Mat& BboxBlob, const ncnn::Mat& LandmarkBlob, float ProdThreshold, std::vector<Face>& Faces);
};
