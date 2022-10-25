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

	int fn = 0;
	Rect r;
	vector<vector<Point>> cont;
	Mat img, gray, mask, dest;
	while (1) {
		cap >> img;
		if (img.empty())
			break;

		//szürkeskálássá alakítás
		cvtColor(img, gray, COLOR_BGR2GRAY);

		//az ég maszkja
		inRange(gray, 100, 155, mask);

		//a sas maszkja
		mask = 255 - mask;

		//a maszk kiterjesztése
		dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(11, 11)));


		findContours(mask, cont, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		//kihasználva, hogy a sas az egyetlen objektum a képen
		r = boundingRect(cont[0]);

		//a kép r téglalap által megadott része
		dest = img(r);

		//megjelenítés
		//imshow("dest", dest);
		//waitKey(33);

		//mentés
		imwrite("sas_" + to_string(fn) + ".png", dest);

		fn += 1;
	}

	return 0;
}