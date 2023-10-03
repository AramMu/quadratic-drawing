#include "circle.h"
#include "alg.h"
class Line {
public:
    Line(cv::Point2d p, cv::Point2d v) {
        a = v.x;
        b = v.y;
        c = -v.x*p.x - v.y*p.y;
    }

    double a,b,c;
};

//double sqr(double x) {
//    return x*x;
//}
double determinant (double a, double b, double c, double d) {
    return a*d - b*c;
}

bool intersection (Line l1, Line l2, cv::Point2d& p) {
    double det = determinant(l1.a, l1.b, l2.a, l2.b);
    if (det == 0) {
        return false;
    }
    p.x = determinant(-l1.c, l1.b, -l2.c, l2.b) / det;
    p.y = determinant(l1.a, -l1.c, l2.a, -l2.c) / det;
    return true;
//            a1x + b1y + c1 = 0
//            a2x + b2y + c2 = 0
}

Circle::Circle(cv::Point2d p1in, cv::Point2d p2in, cv::Point2d p3in) {
    cv::Point2d p1 = (p1in + p2in) / 2.0;
    cv::Point2d p2 = (p1in + p3in) / 2.0;
    cv::Point2d v1 = p2in - p1in;
    cv::Point2d v2 = p3in - p1in;
    //v1 = {v1.y, -v1.x};
    //v2 = {v2.y, -v2.x};
    Line l1(p1, v1);
    Line l2(p2, v2);
    cv::Point2d c;
    if (intersection(l1, l2, c)) {
        this->c = c;
        this->r = sqrt(sqr(p1in.x - c.x) + sqr(p1in.y - c.y));
    } else {
        r = 0;
        this->c = p1in;
    }
}
