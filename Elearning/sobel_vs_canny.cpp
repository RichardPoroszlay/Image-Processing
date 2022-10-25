/**
* OpenCV gyakorlat
* Éldetektálás Sobel és Canny operátor segítségével
*/

#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

///
/// Éldetektálás Sobel operátorral
///
void SobelElek(const Mat img, Mat& dest) {
	//Derivált meghatározásra
	Mat gx, gy, g;
	Sobel(img, gx, CV_16S, 1, 0);  // fuggoletes iranyu elek kiemelese
	Sobel(img, gy, CV_16S, 0, 1);  // vizszintes iranyu elek kiemelese 
	g = abs(gx) + abs(gy);  //a derivált

	//Bájtra konvertõl
	convertScaleAbs(g, g);

	//Automatikus küszöbölás
	threshold(g, dest, 0, 255, THRESH_OTSU);
}


///
/// Éldetektálás Canny operátorral
///
void CannyElek(const Mat img, Mat& dest, int th1) {
	assert(th1 * 3 < 255);
	Canny(img, dest, th1, th1 * 3);
}

int main() {

	Mat img = imread("go2.png", IMREAD_GRAYSCALE);

	assert(!img.empty());

	//Szõrös (tompítja a zajokat)	
	cv::GaussianBlur(img, img, cv::Size(5, 5), 1.6, 1.6);

	Mat sobel, canny;
	SobelElek(img, sobel);
	CannyElek(img, canny, 25);

	imshow("Sobel elek", sobel);
	imshow("Canny elek", canny);
	waitKey(0);

	return 0;
}
