/**
* OpenCV gyakorlat
* Gradiens számítás Sobel operátorral
*/

#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void megjelenit(const string ablak, const Mat img) {
	Mat gviz;
	convertScaleAbs(img, gviz);
	imshow(ablak, gviz);
}


int main() {

	Mat img = imread("go2.png", IMREAD_GRAYSCALE);

	assert(!img.empty());

	//Szõrös (tompítja a zajokat)	
	cv::GaussianBlur(img, img, cv::Size(5, 5), 1.6, 1.6);

	//Derivált közelítése
	Mat gx, gy, g;
	Sobel(img, gx, CV_16S, 1, 0);  // fuggoletes iranyu elek kiemelese
	Sobel(img, gy, CV_16S, 0, 1);  // vizszintes iranyu elek kiemelese 
	g = abs(gx) + abs(gy);  //a derivált

	megjelenit("x szerinti derivalt", gx);
	megjelenit("y szerinti derivalt", gy);
	megjelenit("derivalt kozelitese", g);


	//Derivált valós számokkal
	Mat gxv, gyv, gv;
	Sobel(img, gxv, CV_32F, 1, 0);
	Sobel(img, gyv, CV_32F, 0, 1);
	//a derivált: a mul és az sqrt valós mátrixot igényel
	cv::sqrt(gxv.mul(gxv) + gyv.mul(gyv), gv);

	megjelenit("derivalt", gv);

	waitKey(0);

	return 0;
}
