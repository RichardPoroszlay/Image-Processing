/*
1. Olvassa be a palota.jpg képet színesben.
2. Hisztogramtranszformáció segítségével javítson a képen.
3. Mentse el lathato_palota.png néven.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {

	Mat palota = imread("Kepek/palota.jpg", IMREAD_COLOR);
	Mat gray;
	cvtColor(palota, gray, COLOR_BGR2GRAY);

	// fekete feher kepes
	double minVal, maxVal;
	minMaxLoc(gray, &minVal, &maxVal);

	// az uj kep kiszamolasa
	Mat dest = (gray - minVal) * 255 / (maxVal - minVal + 0.000001);

	// mindez gepi modszereket hasznalva
	Mat dest2;
	equalizeHist(gray, dest2);

	imshow("eredeti debrecen deep", gray);
	imshow("vilagositott debreceni deep", dest);
	imshow("geppel vilagositott debreceni deep", dest2);
	waitKey(0);


	return 0;
}