/*
1. Olvassa be valamelyik gombot tartalmazó képet.
2. Küszöbölje a képet automatikus eljárással úgy, hogy az eredménykép fekete - fehér legyen és a gomb legyen fehér az eredmény téren.
3. Mentse el az eredményt valami.jpg néven.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void invertalas(Mat img, Mat& dest) {
	dest = 255 - img;
}


void main() {

	Mat img = imread("Kepek/color_button2.jpg");
	Mat imgGray = imread("Kepek/color_button2.jpg");
	Mat imgBinary;
	Mat imgInvertedBinary;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	threshold(imgGray, imgBinary, 100, 255, THRESH_BINARY);
	bitwise_not(imgBinary, imgInvertedBinary);

	imshow("Inverted Binaryy Image", imgInvertedBinary);

	imwrite("valami.jpg", imgInvertedBinary);

	waitKey(0);
}