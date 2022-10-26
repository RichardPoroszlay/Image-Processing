/*
1. Olvassa be gombokat tartalmaz� k�pet.
2. [Konvert�lja a k�pet HSV sz�nt�rbe.]
3. M�solja �t a z�ld gombokat egy m�sik, azonos m�ret�, fekete k�pre.
4. Jelen�tse meg az eredm�nyt egy ak�rmi nev� ablakban.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void gombMasoloHSV2(const cv::Mat rgb, cv::Mat& dest) {

    Mat hsv;
    cvtColor(rgb, hsv, ColorConversionCodes::COLOR_BGR2HSV);
    // a narancs szinu pontok "kijelolese"  
    Mat mask;
    inRange(hsv, Scalar(36, 0, 0), Scalar(86, 255, 255), mask);
    // a maszk feher resze ala eso keppontok masolasa az eredeti rgb keprol az eredmeny kepre
    rgb.copyTo(dest, mask);
}

int main() {
	
	Mat img = imread("Kepek/color_buttons.jpg");

    if (img.empty()) {
        cout << "A kep nem talalhato" << '\n';
        exit(-1);
    }

    Mat dest_hsv2;
    gombMasoloHSV2(img, dest_hsv2);

	imshow("Eredeti", img);
	imshow("HSV k�p", dest_hsv2);
	waitKey(0);

	return 0;
}