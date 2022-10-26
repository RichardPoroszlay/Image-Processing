/////*
////	1. Olvassa be a gombokat tartalmaz� k�pet.
////	2. K�sz�b�lje a k�pet(a feh�r gombok elveszhetnek)
////	3. V�gezzen morfol�giai z�r�st a k�pen 7x7 - es, ellipszis alak� strukt�raelemmel.
////	4. Jelen�tse meg a kapott eredm�nyt.
////*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat gombok = imread("Kepek/color_buttons.jpg", IMREAD_COLOR);
	Mat gray, binary;
	cvtColor(gombok, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 160, 255, THRESH_BINARY_INV);
	Mat S = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	Mat er, dil;
	dilate(binary, dil, S);
	erode(dil, er, S);
	imshow("morph close", er);
	waitKey(0);

	return 0;
}