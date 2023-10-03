#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "alg.h"

class Ellipse {
public:
    Ellipse (double a, double b, const cv::Point2d& c=cv::Point2d(0,0));
    void draw (cv::Mat& img, double scale, const cv::Scalar& color=cv::Scalar(0,0,255), const int lineSize=3);
    double a,b;
    cv::Point2d c;
};

class Hyperbola {
public:
    Hyperbola (double a, double b, const cv::Point2d& c=cv::Point2d(0,0), bool orient=false);
    void draw (cv::Mat& img, double scale, const  cv::Scalar& color=cv::Scalar(0,0,255), const int lineSize=3);
    double a,b;
    cv::Point2d c;
    bool orient;
};


class Quadratic {
public:
    Quadratic (std::vector <cv::Point2d>& pts);
    Quadratic (Ellipse& e);
    Quadratic (Hyperbola& h);
    void draw (cv::Mat& img, double scale, const cv::Scalar& color=cv::Scalar(0,0,255), int lineSize=3);
private:
    double a,b,c,d,e,f;
};

#endif // QUADRATIC

