// First Class

/*
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


int main() {

	// Exercise: look for fundamental informations
	Mat img = imread("C:/doggo.png", cv::IMREAD_UNCHANGED); // the first parameter will be read as a picture, it won't be changed
	// Mat img = imread("C:/doggo.png", ImreadModes::IMREAD_GRAYSCALE); our picture will be grey because of IMREAD_GRAYSCALE

	Mat img2 = img + 100;	// it makes the picture paler (fakóbb)

	if (img.empty()) {
		cout << "Picture is not available!" << '\n';
		exit(-1);
	}

	cout << "Row(s): " << img.rows << '\n';	// number of row(s)
	cout << "Column(s): " << img.cols << '\n';	// number of column(s)

	int t = img.type();	// type of the given picture
	if (t == CV_8UC1) {
		cout << "8-bit, grayscale" << '\n';
	}
	else if (t == CV_8UC3) {
		cout << "24-bit RGB" << '\n';
	}
	else {
		cout << "Else" << '\n'; // pl. alpha chanel, other bitdepth
	}

	imshow("kep", img); // shows the picture
	imshow("faded", img2);	// shows a faded version of the picture
	waitKey();	// waiting, the picture won't disappear immediately



	return 0;
}
*/