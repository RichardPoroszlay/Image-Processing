//
// A keppel azonos meretu 8-bites, egycsatornas, tiszta fekete kepek letrehozasa. 
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("kurama.jpg");

	if (img.empty()) {
		cout << "Upsz!" << endl;
		exit(-1);
	}

	// azonos meretu fekete kep
	Mat black1 = Mat::zeros(img.size(), CV_8UC1);
	Mat black2 = Mat::zeros(Size(img.cols, img.rows), CV_8UC1);
	Mat black3(img.size(), CV_8UC1); // meg nem fekete, "memoriaszemet"
	black3.setTo(0); // most mar minden pixel 0 intenzitasu => fekete


	imshow("kep", img);
	imshow("kep2", black1);
	imshow("kep3", black2);
	imshow("kep4", black3);
	waitKey(0);

	return 0;
}