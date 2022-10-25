//
// invertalas
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// feltetelezve, hogy korabban megtortent az ellenorzes
void invertalas(Mat img, Mat& dest) {
	dest = 255 - img;
}

// ha nem feltetelezed, hogy korabban megtortent az ellenorzes
void invertalas2(Mat img, Mat& dest) {
	assert(!img.empty() && img.type() == CV_8UC1);
	dest = 255 - img;
}

int main() {

	Mat img = cv::imread("doggo.jpg", IMREAD_GRAYSCALE);

	// ures-e?
	if (img.empty()) {
		cout << "Upsz" << endl;
		exit(-1);
	}

	Mat dest;
	invertalas2(img, dest);

	imshow("eredeti", img);
	imshow("invertalt", dest);

	waitKey();
	return 0;
}