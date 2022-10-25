/*
OpenCV segadanyagok:
Pelda morfologiai szurore
*/

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. fuggvenyek

using namespace std;
using namespace cv;


int main() {

	Mat img = imread("dog.jpg", IMREAD_GRAYSCALE);

	// csak egy picit atmeretezem, 
	// ha a kisebb kepet toltottek le, amit az elozo gyakorlatoknak hasznltunk, akkor tegyek megjegyzesbe
	resize(img, img, Size(img.cols / 2, img.rows / 2));

	Mat binary_img;
	threshold(img, binary_img, 100, 255, THRESH_BINARY);

	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	// zaj eltavolitasa: az erozio 5x5-os szurovel eltavolitaja az ennel kisebb zajokat
	// a dilatacioval a korvonal helyreall valamennyire
	// hasonlo a helyzet, mint a medianszuro eseteben: novelhetjuk a kernel meretet, ha tobb zajt akaruk eltavolitani
	// de a kutya orra is deformalodik majd rendesen
	Mat tmp, dest, dest2;
	morphologyEx(binary_img, dest, MORPH_OPEN, se);

	imshow("original", img);
	imshow("binary_img", binary_img);
	imshow("MORPH_OPEN=erode+dilate", dest);

	waitKey(0);
}