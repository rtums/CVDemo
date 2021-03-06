//
// Created by jerett on 2019-08-19.
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/optflow.hpp>

using namespace cv;


//cv::Mat DrawFlow(const cv::Mat &flow) {
//    Mat flow_uv[2];
//    Mat mag, ang;
//    Mat hsv_split[3], hsv, rgb;
//
//    split(flow, flow_uv);
//    multiply(flow_uv[1], -1, flow_uv[1]);
//    cartToPolar(flow_uv[0], flow_uv[1], mag, ang, true);
//    normalize(mag, mag, 0, 1, NORM_MINMAX);
//    hsv_split[0] = ang;
//    hsv_split[1] = mag;
//    hsv_split[2] = Mat::ones(ang.size(), ang.type());
//    merge(hsv_split, 3, hsv);
//    // std::cout << "hsv type:" << hsv.type() << std::endl;
//    cvtColor(hsv, rgb, COLOR_HSV2BGR);
//    return rgb;
//}

cv::Mat Flow2Disparity(const cv::Mat &flow) {
    Mat flow_uv[2];
    Mat mag, ang;
    Mat hsv_split[3], hsv, rgb;

    split(flow, flow_uv);
    //multiply(flow_uv[1], -1, flow_uv[1]);
    //cartToPolar(flow_uv[0], flow_uv[1], mag, ang, true);
    //normalize(mag, mag, 0, 1, NORM_MINMAX);
    //hsv_split[0] = ang;
    //hsv_split[1] = mag;
    //hsv_split[2] = Mat::ones(ang.size(), ang.type());
    //merge(hsv_split, 3, hsv);
    //// std::cout << "hsv type:" << hsv.type() << std::endl;
    //cvtColor(hsv, rgb, COLOR_HSV2BGR);
    return flow_uv[0];
}

cv::Mat flow;
cv::Mat disparity;

void TestOpticalFlow(const cv::Mat &img1, const cv::Mat &img2) {
    cv::Mat img1_gray;
    cv::Mat img2_gray;

    cvtColor(img1, img1_gray, cv::COLOR_BGR2GRAY);
    cvtColor(img2, img2_gray, cv::COLOR_BGR2GRAY);

    //cv::Mat flow;
    auto dis_flow = DISOpticalFlow::create(DISOpticalFlow::PRESET_MEDIUM);
    dis_flow->calc(img1_gray, img2_gray, flow);

	//auto flow_draw = DrawFlow(flow);
    flow = Flow2Disparity(flow);
    //imshow("flow", flow_draw);
    //cv::imshow("img1", img1_gray);
    //cv::imshow("img2", img2_gray);
    //cv::waitKey(0);
}

void TestSGBM(const cv::Mat &img1, const cv::Mat &img2) {
    cv::Mat img1_gray;
    cv::Mat img2_gray;

    cvtColor(img1, img1_gray, cv::COLOR_BGR2GRAY);
    cvtColor(img2, img2_gray, cv::COLOR_BGR2GRAY);

    //cv::Mat flow;
    //auto sgbm = StereoSGBM::create(0, 96, 9);
    auto sgbm = StereoSGBM::create(0, 96, 9);
    //cv::Mat disparity;
    sgbm->compute(img1_gray, img2_gray, disparity);
    //dis_flow->calc(img1_gray, img2_gray, flow);

    //auto flow_draw = DrawFlow(flow);
    //imshow("flow", flow_draw);
    //cv::imshow("img1", img1_gray);
    //cv::imshow("img2", img2_gray);
    //cv::waitKey(0);
}



int main(int argc, char *argv[]) {
    //auto img1 = cv::imread("flow_1.jpg");
    //auto img2 = cv::imread("flow_2.jpg");
    auto img1 = cv::imread("cylinder00.bmp");
    auto img2 = cv::imread("cylinder01.bmp");

    TestOpticalFlow(img1, img2);
	TestSGBM(img1, img2);

    return 0;
}
