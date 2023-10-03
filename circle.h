#ifndef CIRCLE_H
#define CIRCLE_H
#include <opencv2/opencv.hpp>

class Circle
{
public:
    Circle(cv::Point2d p1in, cv::Point2d p2in, cv::Point2d p3in);

    double r;
    cv::Point2d c;
};

#endif // CIRCLE_H
