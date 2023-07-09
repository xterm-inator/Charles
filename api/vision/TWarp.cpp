//
// Created by David on 9/07/2023.
//

#include "TWarp.h"
#include "Face.h"

inline double CountAngle(float Landmark[5][2])
{
    double A = Landmark[2][1] - (Landmark[0][1] + Landmark[1][1]) / 2;
    double B = Landmark[2][0] - (Landmark[0][0] + Landmark[1][0]) / 2;
    double angle = atan(abs(B) / A) * 180.0 / M_PI;
    return angle;
}

cv::Mat TWarp::Process(cv::Mat& SmallFrame, Face& Face)
{
    // gt face landmark
    float v1[5][2] = {
            {30.2946f, 51.6963f},
            {65.5318f, 51.5014f},
            {48.0252f, 71.7366f},
            {33.5493f, 92.3655f},
            {62.7299f, 92.2041f}
    };
    static cv::Mat src(5, 2, CV_32FC1, v1);
    memcpy(src.data, v1, 2*5*sizeof(float));

    // Perspective Transformation
    float v2[5][2] ={
        {Face.FaceImageLandmarks[0].x, Face.FaceImageLandmarks[0].y},
        {Face.FaceImageLandmarks[1].x, Face.FaceImageLandmarks[1].y},
        {Face.FaceImageLandmarks[2].x, Face.FaceImageLandmarks[2].y},
        {Face.FaceImageLandmarks[3].x, Face.FaceImageLandmarks[3].y},
        {Face.FaceImageLandmarks[4].x, Face.FaceImageLandmarks[4].y},
    };
    cv::Mat dst(5, 2, CV_32FC1, v2);
    memcpy(dst.data, v2, 2*5*sizeof(float));

    // compute the turning angle
    Angle = CountAngle(v2);

    cv::Mat aligned = SmallFrame.clone();
    cv::Mat m = SimilarTransform(dst, src);
    cv::warpPerspective(SmallFrame, aligned, m, cv::Size(96, 112), cv::INTER_LINEAR);
    resize(aligned, aligned, cv::Size(112, 112), 0, 0, cv::INTER_LINEAR);

    return aligned;
}

int TWarp::MatrixRank(cv::Mat M)
{
    cv::Mat w, u, vt;
    cv::SVD::compute(M, w, u, vt);
    cv::Mat1b nonZeroSingularValues = w > 0.0001;
    int rank = countNonZero(nonZeroSingularValues);
    return rank;
}

cv::Mat TWarp::VarAxis0(const cv::Mat& Src)
{
    cv::Mat temp_ = ElementwiseMinus(Src,MeanAxis0(Src));
    cv::multiply(temp_ ,temp_ ,temp_ );
    return MeanAxis0(temp_);
}

cv::Mat TWarp::MeanAxis0(const cv::Mat& Src)
{
    int num = Src.rows;
    int dim = Src.cols;

    // x1 y1
    // x2 y2
    cv::Mat output(1,dim,CV_32F);
    for(int i = 0 ; i <  dim; i++){
        float sum = 0 ;
        for(int j = 0 ; j < num ; j++){
            sum+=Src.at<float>(j,i);
        }
        output.at<float>(0,i) = sum/num;
    }

    return output;
}

cv::Mat TWarp::ElementwiseMinus(const cv::Mat& A, const cv::Mat& B)
{
    cv::Mat output(A.rows,A.cols,A.type());

    assert(B.cols == A.cols);
    if(B.cols == A.cols)
    {
        for(int i = 0 ; i <  A.rows; i ++)
        {
            for(int j = 0 ; j < B.cols; j++)
            {
                output.at<float>(i,j) = A.at<float>(i,j) - B.at<float>(0,j);
            }
        }
    }
    return output;
}

cv::Mat TWarp::SimilarTransform(cv::Mat Src, cv::Mat Dst)
{
    int num = Src.rows;
    int dim = Src.cols;
    cv::Mat src_mean = MeanAxis0(Src);
    cv::Mat dst_mean = MeanAxis0(Dst);
    cv::Mat src_demean = ElementwiseMinus(Src, src_mean);
    cv::Mat dst_demean = ElementwiseMinus(Dst, dst_mean);
    cv::Mat A = (dst_demean.t() * src_demean) / static_cast<float>(num);
    cv::Mat d(dim, 1, CV_32F);
    d.setTo(1.0f);
    if (cv::determinant(A) < 0) {
        d.at<float>(dim - 1, 0) = -1;

    }
    cv::Mat T = cv::Mat::eye(dim + 1, dim + 1, CV_32F);
    cv::Mat U, S, V;

    // the SVD function in opencv differ from scipy .
    cv::SVD::compute(A, S,U, V);

    int rank = MatrixRank(A);
    if (rank == 0) {
        assert(rank == 0);

    } else if (rank == dim - 1) {
        if (cv::determinant(U) * cv::determinant(V) > 0) {
            T.rowRange(0, dim).colRange(0, dim) = U * V;
        } else {
//            s = d[dim - 1]
//            d[dim - 1] = -1
//            T[:dim, :dim] = np.dot(U, np.dot(np.diag(d), V))
//            d[dim - 1] = s
            int s = d.at<float>(dim - 1, 0) = -1;
            d.at<float>(dim - 1, 0) = -1;

            T.rowRange(0, dim).colRange(0, dim) = U * V;
            cv::Mat diag_ = cv::Mat::diag(d);
            cv::Mat twp = diag_*V; //np.dot(np.diag(d), V.T)
            cv::Mat B = cv::Mat::zeros(3, 3, CV_8UC1);
            cv::Mat C = B.diag(0);
            T.rowRange(0, dim).colRange(0, dim) = U* twp;
            d.at<float>(dim - 1, 0) = s;
        }
    }
    else{
        cv::Mat diag_ = cv::Mat::diag(d);
        cv::Mat twp = diag_*V.t(); //np.dot(np.diag(d), V.T)
        cv::Mat res = U* twp; // U
        T.rowRange(0, dim).colRange(0, dim) = -U.t()* twp;
    }
    cv::Mat var_ = VarAxis0(src_demean);
    float val = cv::sum(var_).val[0];
    cv::Mat res;
    cv::multiply(d,S,res);
    float scale =  1.0/val*cv::sum(res).val[0];
    T.rowRange(0, dim).colRange(0, dim) = - T.rowRange(0, dim).colRange(0, dim).t();
    cv::Mat temp1 = T.rowRange(0, dim).colRange(0, dim); // T[:dim, :dim]
    cv::Mat temp2 = src_mean.t(); //src_mean.T
    cv::Mat temp3 = temp1*temp2; // np.dot(T[:dim, :dim], src_mean.T)
    cv::Mat temp4 = scale*temp3;
    T.rowRange(0, dim).colRange(dim, dim+1)=  -(temp4 - dst_mean.t()) ;
    T.rowRange(0, dim).colRange(0, dim) *= scale;
    return T;
}
