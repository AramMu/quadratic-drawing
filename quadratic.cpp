#include "quadratic.h"

Ellipse::Ellipse (double a, double b, const cv::Point2d& c) : a(a), b(b), c(c) {}
void Ellipse::draw (cv::Mat& img, double scale, const cv::Scalar& color, const int lineSize) {
    Quadratic q(*this);
    q.draw(img, scale, color, lineSize);
}



Hyperbola::Hyperbola (double a, double b, const cv::Point2d& c, bool orient) : a(a), b(b), c(c), orient(orient) {}
void Hyperbola::draw (cv::Mat& img, double scale, const cv::Scalar& color, const int lineSize){
    Quadratic q(*this);
    q.draw(img, scale, color, lineSize);
}







Quadratic::Quadratic (std::vector <cv::Point2d>& pts) {
    if (pts.size() != 5) return;
    matrix m(5,std::vector <double>(6));
    for (int i = 0; i < 5; ++i) {
        m[i][0] = sqr(pts[i].x);
        m[i][1] = pts[i].x * pts[i].y;
        m[i][2] = sqr(pts[i].y);
        m[i][3] = pts[i].x;
        m[i][4] = pts[i].y;
        m[i][5] = -1;
    }
    std::vector <double> res = solveLinear(m);
    a=res[0]; b=res[1]; c=res[2]; d=res[3]; e=res[4]; f=1;
}

Quadratic::Quadratic (Ellipse& el) {
    a = sqr(el.b);
    b = 0;
    c = sqr(el.a);
    d = -2*sqr(el.b)*el.c.x;
    e = -2*sqr(el.a)*el.c.y;
    f = sqr(el.b)*sqr(el.c.x) + sqr(el.a)*sqr(el.c.y) - sqr(el.a)*sqr(el.b);
}

Quadratic::Quadratic (Hyperbola& hy) {
    a = sqr(hy.b);
    b = 0;
    c = -sqr(hy.a);
    d = -2*sqr(hy.b)*hy.c.x;
    e = 2*sqr(hy.a)*hy.c.y;
    if (hy.orient) {
        a=-a; c=-c;
        d=-d; e=-e;
    }
    f = -sqr(hy.a)*sqr(hy.b);
    if (hy.orient) f += -sqr(hy.b)*sqr(hy.c.x) + sqr(hy.a)*sqr(hy.c.y);
    else f += sqr(hy.b)*sqr(hy.c.x) - sqr(hy.a)*sqr(hy.c.y);
}

void Quadratic::draw (cv::Mat& img, double scale, const cv::Scalar& color, int lineSize) {
    //const cv::Scalar RED (0,0,255);
    for (int i = 0; i < img.cols; ++i) {
        double x = i/scale, y1, y2;
        if (c==0) {
            y1 = -(a*x*x+d*x+f) / (b*x+e);
            y2 = -1;
        } else {
            double disc = sqr(b*x+e) - 4*c*(a*x*x + d*x + f);
            if (disc<0) {
                y1=-1;
                y2=-1;
            } else {
                y1 = (-(b*x+e) + sqrt(disc))/(2*c);
                y2 = (-(b*x+e) - sqrt(disc))/(2*c);
            }
        }
        int j1 = y1*scale;
        int j2 = y2*scale;
        if (j1>=0) {
            cv::circle(img,cv::Point(i,j1),lineSize,color,-1);
        }
        if (j2>=0) {
            cv::circle(img,cv::Point(i,j2),lineSize,color,-1);
        }
    }


    for (int i = 0; i < img.rows; ++i) {
        double y = i/scale, x1, x2;
        if (a==0) {
            x1 = -(c*y*y+e*y+f) / (b*y+d);
            x2 = -1;
        } else {
            double disc = sqr(b*y+d) - 4*a*(c*y*y + e*y + f);
            if (disc<0) {
                x1=-1;
                x2=-1;
            } else {
                x1 = (-(b*y+d) + sqrt(disc))/(2*a);
                x2 = (-(b*y+d) - sqrt(disc))/(2*a);
            }
        }

        int j1 = x1*scale;
        int j2 = x2*scale;
        if (j1>=0) {
            cv::circle(img,cv::Point(j1,i),lineSize,color,-1);
        }
        if (j2>=0) {
            cv::circle(img,cv::Point(j2,i),lineSize,color,-1);
        }
    }
}
