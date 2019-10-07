#include "median_filter_plugin.h"


Median_filter_plugin::Median_filter_plugin()
{
}

Median_filter_plugin::~Median_filter_plugin()
{

}

QString Median_filter_plugin::description()
{
    return "This plugin applies median blur filters to any image."
            "This plugin's goal is to make us more familiar with the"
            "concept of plugins in general.";
}

void Median_filter_plugin::processImage(const cv::Mat &inpImage, cv::Mat &outImage)
{
    cv::medianBlur(inpImage, outImage,5);
}
