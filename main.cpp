#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "quadratic.h"
#include "circle.h"
#include "alg.h"

using namespace std;

vector <cv::Point2d> pts;
cv::Mat img = cv::Mat(500,500,CV_8UC3,cv::Scalar(0,0,0));

class Polynom {
public:
    vector <double> coef;
    Polynom () {}
    Polynom (vector <cv::Point2d>& pts) {
        int n = pts.size();
        matrix x(n, vector <double>(n+1));
        for (int i = 0; i < n; ++i) {
            x[i][n] = pts[i].y;
        }
        for (int i = 0; i < n; ++i) {
            double st=1;
            for (int j = 0; j < n; ++j) {
                x[i][j] = st;
                st *= pts[i].x;
            }
        }
        coef = solveLinear (x);
    }

    double calc (double x) {
        double res=0;
        for (int i = coef.size()-1; i >= 0; i--) {
            res = res*x + coef[i];
        }
        return res;
    }

    void draw (cv::Mat& img, double scale) {
        const cv::Scalar RED (0,0,255);
        cv::Point prev(-1,-1);
        for (int i = 0; i < img.cols; ++i) {
            if (prev.x>=0) {
                cv::line(img, prev, cv::Point(i, calc(i/scale)*scale),RED,3);
            }
            prev = cv::Point(i, calc(i/scale)*scale);
            cv::circle(img, cv::Point(i, calc(i/scale)*scale),3,RED,-1);
        }
    }
};


void CallBackFunc(int event, int xPos, int yPos, int flags, void* userdata){
    if  ( event != cv::EVENT_LBUTTONDOWN ){
        return;
    }
    double scale = 100.0;
    const cv::Scalar WHITE (255,255,255);
    const cv::Scalar RED(0,0,255);
    pts.push_back(cv::Point2d (xPos/scale, yPos/scale));
    cv::circle(img, cv::Point(xPos, yPos),3,WHITE,-1);
    cv::imshow("aaa", img);

    /*
    if (pts.size()==5) {
        Quadratic q(pts);
        q.draw (img, scale);
        for (int i = 0; i < pts.size(); ++i) {
            cv::circle(img, cv::Point(pts[i].x*scale, pts[i].y*scale),3,WHITE,-1);
        }
        cv::imshow("aaa",img);
    }
    */

    if (pts.size()==3) {
        Circle c(pts[0], pts[1], pts[2]);
        cv::circle(img, c.c*scale, c.r*scale, RED, 3);
        for (int i = 0; i < pts.size(); ++i) {
            cv::circle(img, cv::Point(pts[i].x*scale, pts[i].y*scale),3,WHITE,-1);
        }
        cv::imshow("aaa",img);
    }
}


/*
void CallBackFunc(int event, int xPos, int yPos, int flags, void* userdata){
    //std::cout << "Called\n";
    if  ( event != cv::EVENT_LBUTTONDOWN ){
        return;
    }

    double scale = 100.0;
    const cv::Scalar WHITE (255,255,255);
    pts.push_back(cv::Point2d (xPos/scale, yPos/scale));
    img = cv::Mat (500,500, CV_8UC3, cv::Scalar::all(0));
    for (int i = 0; i < pts.size(); ++i) {
        cv::circle(img, pts[i] * scale,3,WHITE,-1);
    }
    Polynom p(pts);
    p.draw(img, scale);
    for (int i = 0; i < pts.size(); ++i) {
        cv::circle(img, cv::Point(pts[i].x*scale, pts[i].y*scale),3,WHITE,-1);
    }
    cv::imshow("aaa",img);
}
*/

void drawFocalCurve (int type) {
    double foci=10000;
    //type = -1;
    if (type>0) {
        //int n = (int) (img.cols*1.25);
        //double step = n / 512.0;
        double step = sqr((img.cols/2.0*1.38)) / 256;
        for (double i = 0; i < 256; i+=20) {
            cv::Scalar color (cv::Scalar::all(0.8*(255-i)+50));
            Ellipse e(sqrt (foci + step*(i+1)), sqrt (step*(i+1)), cv::Point2d (img.cols/2, img.rows/2));
            e.draw(img, 1.0, color, 1);
        }


        for (double i = 0; i < 256; i+=20) {
            cv::Scalar color (cv::Scalar::all(0.8*(255-i)+50));
            Ellipse e(sqrt (step*(i+1)), sqrt (foci + step*(i+1)), cv::Point2d (img.cols/2, img.rows/2));
            e.draw(img, 1.0, color, 1);
        }
    } else {
        //int n = foci;
        //double step = n / 257.0;
        double step = foci / 256.0;

        for (double i = 0; i < 256; i+=20) {
            cv::Scalar color (cv::Scalar::all(0.8*(255-i)+50));
            Hyperbola h( sqrt (foci - step*(i+1)), sqrt(step*(i+1)), cv::Point2d (img.cols/2, img.rows/2));
            h.draw(img, 1.0, color, 1);
        }


        step = foci / 256.0;
        for (double i = 0; i < 256; i+=20) {
            cv::Scalar color (cv::Scalar::all(0.8*(255-i)+50));
            Hyperbola h(sqrt(step*(i+1)), sqrt (foci - step*(i+1)), cv::Point2d (img.cols/2, img.rows/2), true);
            h.draw(img, 1.0, color, 1);
        }
    }
}

int main(){
    cv::namedWindow("aaa");
    //drawFocalCurve(1);
    //drawFocalCurve(-1);
    //Hyperbola h(100, 100, cv::Point2d(250,250), false);
    //h.draw(img,1,cv::Scalar::all(255),1);
    //Ellipse e(0, 100, cv::Point2d(250,250));
    //e.draw(img,1,cv::Scalar::all(255),1);
    cv::imshow("aaa",img);
    //cv::waitKey(0);

    cv::setMouseCallback("aaa",CallBackFunc);
    while (true) {
        cv::imshow("aaa", img);
        cv::waitKey(0);
        pts.clear();
        img = cv::Mat (500,500, CV_8UC3, cv::Scalar::all(0));
    }

    return 0;
}

