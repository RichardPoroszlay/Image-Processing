/**
A videó részlet az alábbi címrõl van
https://www.youtube.com/watch?v=thEkFMaB5CA
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	VideoCapture cap;
	cap.open("sas.avi");

	if (!cap.isOpened()) {
		cout << "error" << endl;
		return -1;
	}

	Mat img, gray, mask, dest;
	while (1) {
		cap >> img;
		if (img.empty())
			break;

		cvtColor(img, gray, COLOR_BGR2GRAY);
		inRange(gray, 100, 155, mask);

		dest = img.clone();
		medianBlur(mask, mask, 5);
		dest.setTo(0, mask);

		imshow("src", img);
		imshow("dest", dest);

		waitKey(200);
	}
	waitKey(0);

	return 0;
}
