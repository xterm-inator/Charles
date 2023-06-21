//
// Created by David on 15/04/2023.
//

#include <opencv2/opencv.hpp>

#include "TRetina.h"
#include "Face.h"
#include "Image.h"

TRetina::TRetina(unsigned int Width, unsigned int Height)
{
    ImgWidth = Width;
    ImgHeight = Height;

    RetinaFace.opt.use_vulkan_compute = true;
    RetinaFace.load_param("../models/retina/mnet.25-opt.param");
    RetinaFace.load_model("../models/retina/mnet.25-opt.bin");
}

TRetina::~TRetina() = default;

int TRetina::DetectFace(Image& Image, std::vector<Face>& Faces)
{
//    cv::Mat Frame;
//
//    float ScaleX = ((float) Frame.cols) / RetinaWidth;
//    float ScaleY = ((float) Frame.rows) / RetinaHeight;
//
//     cv::resize(image.RawImage, Frame, cv::Size(RetinaWidth,RetinaHeight),cv::INTER_LINEAR);
//
//     return 0;

//    ncnn::Mat In = ncnn::Mat(ImgHeight, ImgWidth, ncnn::Mat::PIXEL_RGB,image.RawImage);
    ncnn::Mat In = ncnn::Mat::from_pixels(Image.RawImage.data, ncnn::Mat::PIXEL_BGR2RGB, ImgWidth, ImgHeight);

    ncnn::Extractor Extractor = RetinaFace.create_extractor(); //every time use a new extractor to clear internal caches

    Extractor.input("data", In);

    std::vector<Face> FaceProposals;

    // stride 32
    {
        ncnn::Mat ScoreBlob, BboxBlob, LandmarkBlob;
        Extractor.extract("face_rpn_cls_prob_reshape_stride32", ScoreBlob);
        Extractor.extract("face_rpn_bbox_pred_stride32", BboxBlob);
        Extractor.extract("face_rpn_landmark_pred_stride32", LandmarkBlob);

        const int BaseSize = 16;
        const int FeatStride = 32;
        ncnn::Mat Ratios(1);
        Ratios[0] = 1.f;
        ncnn::Mat Scales(2);
        Scales[0] = 32.f;
        Scales[1] = 16.f;
        ncnn::Mat Anchors = GenerateAnchors(BaseSize, Ratios, Scales);

        std::vector<Face> Face32;
        GenerateProposals(Anchors, FeatStride, ScoreBlob, BboxBlob, LandmarkBlob, ProbThreshold, Face32);

        FaceProposals.insert(FaceProposals.end(), Face32.begin(), Face32.end());
    }

//    // stride 16
//    {
//        ncnn::Mat ScoreBlob, BboxBlob, LandmarkBlob;
//        Extractor.extract("face_rpn_cls_prob_reshape_stride16", ScoreBlob);
//        Extractor.extract("face_rpn_bbox_pred_stride16", BboxBlob);
//        Extractor.extract("face_rpn_landmark_pred_stride16", LandmarkBlob);
//
//        const int BaseSize = 16;
//        const int FeatStride = 16;
//        ncnn::Mat Ratios(1);
//        Ratios[0] = 1.f;
//        ncnn::Mat Scales(2);
//        Scales[0] = 8.f;
//        Scales[1] = 4.f;
//        ncnn::Mat Anchors = GenerateAnchors(BaseSize, Ratios, Scales);
//
//        std::vector<Face> Face16;
//        GenerateProposals(Anchors, FeatStride, ScoreBlob, BboxBlob, LandmarkBlob, ProbThreshold, Face16);
//
//        FaceProposals.insert(FaceProposals.end(), Face16.begin(), Face16.end());
//    }
//
//    // stride 8
//    {
//        ncnn::Mat ScoreBlob, BboxBlob, LandmarkBlob;
//        Extractor.extract("face_rpn_cls_prob_reshape_stride8", ScoreBlob);
//        Extractor.extract("face_rpn_bbox_pred_stride8", BboxBlob);
//        Extractor.extract("face_rpn_landmark_pred_stride8", LandmarkBlob);
//
//        const int BaseSize = 16;
//        const int FeatStride = 8;
//        ncnn::Mat Ratios(1);
//        Ratios[0] = 1.f;
//        ncnn::Mat Scales(2);
//        Scales[0] = 2.f;
//        Scales[1] = 1.f;
//        ncnn::Mat Anchors = GenerateAnchors(BaseSize, Ratios, Scales);
//
//        std::vector<Face> Face8;
//        GenerateProposals(Anchors, FeatStride, ScoreBlob, BboxBlob, LandmarkBlob, ProbThreshold, Face8);
//
//        FaceProposals.insert(FaceProposals.end(), Face8.begin(), Face8.end());
//    }

    return FaceProposals.size();

//    // sort all proposals by score from highest to lowest
//    QSortDescentInplace(FaceProposals);
//
//    // apply nms with NMSThreshold
//    std::vector<int> Picked;
//    NMSSortedBboxes(FaceProposals, Picked, NMSThreshold);
//
//    int FaceCount = Picked.size();
//
//    return FaceCount;
//
//    Faces.resize(FaceCount);
//
//    for (int i = 0; i < FaceCount; i++)
//    {
//        Faces[i] = FaceProposals[Picked[i]];
//
//        // clip to image size
//        float x0 = Faces[i].BoundingBox.x;
//        float y0 = Faces[i].BoundingBox.y;
//        float x1 = x0 + Faces[i].BoundingBox.width;
//        float y1 = y0 + Faces[i].BoundingBox.height;
//
//        x0 = std::max(std::min(x0, (float)ImgWidth - 1), 0.f);
//        y0 = std::max(std::min(y0, (float)ImgHeight - 1), 0.f);
//        x1 = std::max(std::min(x1, (float)ImgWidth - 1), 0.f);
//        y1 = std::max(std::min(y1, (float)ImgHeight - 1), 0.f);
//
//        Faces[i].BoundingBox.x = x0;
//        Faces[i].BoundingBox.y = y0;
//        Faces[i].BoundingBox.width = x1 - x0;
//        Faces[i].BoundingBox.height = y1 - y0;
//    }
//
//    return Faces.size();
    return 0;
}

static inline float IntersectionArea(const Face& a, const Face& b)
{
    cv::Rect_<float> inter = a.BoundingBox & b.BoundingBox;
    return inter.area();
}

void TRetina::QSortDescentInplace(std::vector<Face> &Faces, int Left, int Right)
{
    int i = Left;
    int j = Right;
    float p = Faces[(Left + Right) / 2].FaceProb;

    while(i <= j){
        while(Faces[i].FaceProb > p) i++;
        while(Faces[j].FaceProb < p) j--;
        if(i<=j){
            // swap
            std::swap(Faces[i], Faces[j]);
            i++; j--;
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (Left < j) QSortDescentInplace(Faces, Left, j);
        }
        #pragma omp section
        {
            if (i < Right) QSortDescentInplace(Faces, i, Right);
        }
    }
}

void TRetina::QSortDescentInplace(std::vector<Face>& Faces)
{
    if (Faces.empty())
        return;

    QSortDescentInplace(Faces, 0, Faces.size() - 1);
}

void TRetina::NMSSortedBboxes(const std::vector<Face> &Faces, std::vector<int> &Picked, float Threshold)
{
    Picked.clear();

    const int n = Faces.size();

    std::vector<float> areas(n);
    for (int i = 0; i < n; i++)
    {
        areas[i] = Faces[i].BoundingBox.area();
    }

    for (int i = 0; i < n; i++)
    {
        const Face& a = Faces[i];

        int keep = 1;
        for (int j : Picked)
        {
            const Face& b = Faces[j];

            // intersection over union
            float inter_area = IntersectionArea(a, b);
            float union_area = areas[i] + areas[j] - inter_area;
            //             float IoU = inter_area / union_area
            if (inter_area / union_area > Threshold)
                keep = 0;
        }

        if (keep)
        {
            Picked.push_back(i);
        }
    }
}

ncnn::Mat TRetina::GenerateAnchors(int BaseSize, const ncnn::Mat &Ratios, const ncnn::Mat &Scales)
{
    int NumRatio = Ratios.w;
    int NumScale = Ratios.w;

    ncnn::Mat Anchors;
    Anchors.create(4, NumRatio * NumScale);

    const float cx = BaseSize * 0.5f;
    const float cy = BaseSize * 0.5f;

    for (int i = 0; i < NumRatio; i++)
    {
        float ar = Scales[i];

        int r_w = round(BaseSize / sqrt(ar));
        int r_h = round(r_w * ar); //round(base_size * sqrt(ar));

        for (int j = 0; j < NumScale; j++)
        {
            float scale = Scales[j];

            float rs_w = r_w * scale;
            float rs_h = r_h * scale;

            float* anchor = Anchors.row(i * NumScale + j);

            anchor[0] = cx - rs_w * 0.5f;
            anchor[1] = cy - rs_h * 0.5f;
            anchor[2] = cx + rs_w * 0.5f;
            anchor[3] = cy + rs_h * 0.5f;
        }
    }

    return Anchors;
}

void TRetina::GenerateProposals(const ncnn::Mat &Anchors, int FeatStride, const ncnn::Mat &ScoreBlob,
                                const ncnn::Mat &BboxBlob, const ncnn::Mat &LandmarkBlob, float ProdThreshold,
                                std::vector<Face> &Faces)
{
    int W = ScoreBlob.w;
    int H = ScoreBlob.h;

    // generate face proposal from bbox deltas and shifted anchors
    const int NumAnchors = Anchors.h;

    for (int q = 0; q < NumAnchors; q++)
    {
        const float* Anchor = Anchors.row(q);

        const ncnn::Mat score = ScoreBlob.channel(q + NumAnchors);
        const ncnn::Mat bbox = BboxBlob.channel_range(q * 4, 4);
        const ncnn::Mat landmark = LandmarkBlob.channel_range(q * 10, 10);

        // shifted anchor
        float AnchorY = Anchor[1];

        float AnchorW = Anchor[2] - Anchor[0];
        float AnchorH = Anchor[3] - Anchor[1];

        for (int i = 0; i < H; i++)
        {
            float AnchorX = Anchor[0];

            for (int j = 0; j < W; j++)
            {
                int index = i * W + j;

                float prob = score[index];

                if (prob >= ProdThreshold)
                {
                    // apply center size
                    float dx = bbox.channel(0)[index];
                    float dy = bbox.channel(1)[index];
                    float dw = bbox.channel(2)[index];
                    float dh = bbox.channel(3)[index];

                    float cx = AnchorX + AnchorW * 0.5f;
                    float cy = AnchorY + AnchorH * 0.5f;

                    float pb_cx = cx + AnchorW * dx;
                    float pb_cy = cy + AnchorH * dy;

                    float pb_w = AnchorW * exp(dw);
                    float pb_h = AnchorH * exp(dh);

                    float x0 = pb_cx - pb_w * 0.5f;
                    float y0 = pb_cy - pb_h * 0.5f;
                    float x1 = pb_cx + pb_w * 0.5f;
                    float y1 = pb_cy + pb_h * 0.5f;

                    Face Obj;
                    Obj.BoundingBox.x = x0;
                    Obj.BoundingBox.y = y0;
                    Obj.BoundingBox.width = (x1 - x0 + 1);
                    Obj.BoundingBox.height = (y1 - y0 + 1);
                    Obj.Landmarks[0].x = cx + (AnchorW + 1) * landmark.channel(0)[index];
                    Obj.Landmarks[0].y = cy + (AnchorH + 1) * landmark.channel(1)[index];
                    Obj.Landmarks[1].x = cx + (AnchorW + 1) * landmark.channel(2)[index];
                    Obj.Landmarks[1].y = cy + (AnchorH + 1) * landmark.channel(3)[index];
                    Obj.Landmarks[2].x = cx + (AnchorW + 1) * landmark.channel(4)[index];
                    Obj.Landmarks[2].y = cy + (AnchorH + 1) * landmark.channel(5)[index];
                    Obj.Landmarks[3].x = cx + (AnchorW + 1) * landmark.channel(6)[index];
                    Obj.Landmarks[3].y = cy + (AnchorH + 1) * landmark.channel(7)[index];
                    Obj.Landmarks[4].x = cx + (AnchorW + 1) * landmark.channel(8)[index];
                    Obj.Landmarks[4].y = cy + (AnchorH + 1) * landmark.channel(9)[index];
                    Obj.FaceProb = prob;

                    Faces.push_back(Obj);
                }
                AnchorX += FeatStride;
            }
            AnchorY += FeatStride;
        }
    }
}
