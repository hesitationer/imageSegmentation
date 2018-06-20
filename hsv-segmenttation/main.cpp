#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


int main(int argc, char *argv[])
{
    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));//可以生成形态学操作中用到的核
    cv::VideoCapture cap("/home/ubuntu/Pictures/pictures/VideoTest.avi");
    cv::Mat colorFrame;
    cv::Mat hsvFrame, threshLow, threshHigh, resultFrame_hsv;
    while(cap.isOpened()&&cv::waitKey(10)!=27)
    {
        cap>>colorFrame;
        cv::imshow("color image",colorFrame);

        cv::cvtColor(colorFrame, hsvFrame, CV_BGR2HSV);
        /**
         * @brief cv::inRange(InputArray src,InputArray lowerb, InputArrayupperb, OutputArray dst)
            @param src first input array.
            @param lowerb inclusive lower boundary array or a scalar.
            @param upperb inclusive upper boundary array or a scalar.
            @param dst output array of the same size as src and CV_8U type.
         */
        cv::inRange(hsvFrame, cv::Scalar(0, 0, 221), cv::Scalar(180, 30, 255), threshLow);
        cv::inRange(hsvFrame, cv::Scalar(165, 155, 155), cv::Scalar(179, 255, 255), threshHigh);
        cv::add(threshLow, threshHigh, resultFrame_hsv);

        // Optional edits for reducing noise
        cv::GaussianBlur(resultFrame_hsv, resultFrame_hsv, cv::Size(5, 5), 0);
        ///形态学变换 膨胀、腐蚀
        cv::dilate(resultFrame_hsv, resultFrame_hsv, structuringElement3x3);
        cv::erode(resultFrame_hsv, resultFrame_hsv, structuringElement3x3);

        cv::imshow("Color Tracking", resultFrame_hsv);
    }

    return 0;

}

