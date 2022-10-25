////
//// kep meretenek, tipusanak lekerdezese
////
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

	cout << "sor: " << img.rows << endl;
	cout << "oszlop: " << img.cols << endl;

	int t = img.type();
	if (t == CV_8UC1)
		cout << "8-bit, szurkeskala" << endl;
	else if (t == CV_8UC3)
		cout << "24-bit RGB" << endl;
	else
		cout << "egyeb" << endl;  // pl. alfa csatorna, mas bitmelyseg

	imshow("kep", img);
	waitKey(0);

	return 0;
}