#include <QCoreApplication>
#include <opencv2/opencv.hpp>

//using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::Mat image = cv::imread("D:/2.jpg");
    cv::imshow("Output",image);
    return a.exec();
}
