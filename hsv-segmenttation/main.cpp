#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <houghLine.h>
#include <auto_canny.h>
using namespace std;
using namespace cv;


int WherePixMap(cv::Mat &image,std::vector<int> &cluster)
{
    int PixRow = 480;
    while(PixRow>0&&cluster.size()<5)
    {
        if(image.at<cv::Vec3b>(320,PixRow)[0]==255)
            if(PixRow-cluster[0]<10)
                cluster.push_back(PixRow);
        PixRow --;
    }
    if(cluster.size()==5)
    {
        int sum = std::accumulate(std::begin(cluster), std::end(cluster), 0);
        double mean =  sum / cluster.size(); //均值
        cluster.clear();
        return mean;
    }
    cluster.clear();
    return 0;
}


int InitPixRow(cv::Mat image)
{
    int PixRow = 480;
    while(PixRow>0)
    {
        if(image.at<cv::Vec3b>(320,PixRow)[0]==255)
            return PixRow;
        PixRow --;
    }
    return 480;
}


int main(int argc, char *argv[])
{
    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));//可以生成形态学操作中用到的核
    vector<Vec2f> Window_frame;
    cv::VideoCapture cap("/home/star/mono/VideoTest.avi");
    cout<<"----"<<endl;
    cv::Mat colorFrame;
    cv::Mat hsvFrame/*, threshLow, threshHigh*/, resultFrame_hsv;
    int pos;
    vector<int> cluster;
    while(cap.isOpened()&&cv::waitKey(10)!=27)
    {
        cap>>colorFrame;
        if(colorFrame.empty())
        {
            cout<<"image load compeleted!"<<endl;
            break;
        }

        cv::imshow("color image",colorFrame);

        cv::cvtColor(colorFrame, hsvFrame, CV_RGB2HSV );


        cv::inRange(hsvFrame, cv::Scalar(0, 0, 211), cv::Scalar(180, 43, 255), resultFrame_hsv);

//        cv::inRange(hsvFrame, cv::Scalar(0, 0, 211), cv::Scalar(180, 43, 255), threshLow);
//        cv::inRange(hsvFrame, cv::Scalar(165, 155, 155), cv::Scalar(179, 255, 255), threshHigh);
//        cv::add(threshLow, threshHigh, resultFrame_hsv);

        // Optional edits for reducing noise
        cv::GaussianBlur(resultFrame_hsv, resultFrame_hsv, cv::Size(5, 5), 0);
        cv::dilate(resultFrame_hsv, resultFrame_hsv, structuringElement3x3);
        cv::erode(resultFrame_hsv, resultFrame_hsv, structuringElement3x3);

        cvtColor(resultFrame_hsv,resultFrame_hsv,CV_GRAY2RGB);
        cv::imshow("hsv model",resultFrame_hsv);

        hough_line_detect(resultFrame_hsv,resultFrame_hsv,Window_frame);


//        int inti = InitPixRow(resultFrame_hsv);
//        cluster.push_back(inti);
//        cout<<cluster[0]<<endl;

//        pos = WherePixMap(resultFrame_hsv,cluster);
//        Point pt(320,pos);

//        circle(resultFrame_hsv,pt,10,CV_RGB(0,255,0),2);
//        cout<<pos<<endl;
        cv::imshow("Color Tracking", resultFrame_hsv);
    }

    return 0;

}

