#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void vilagosit1(Mat img) { //Mi�rt v�ltozik az eredeti k�p? V�lasz: mivel azt m�dos�tjuk, nem egy referenci�t
	img = img + 100;
}
void vilagosit2(Mat img, Mat& dest) { //Mi�rt kell az & jel? V�lasz: mert referencia
	dest = img + 100;
}

int main() {

	Mat img = cv::imread("doggo.jpg", IMREAD_GRAYSCALE);

	vilagosit1(img);
	imshow("fako1", img);

	Mat dest; // A k�p m�g �res
	vilagosit2(img, dest);
	imshow("fako2", dest);

	waitKey();
	return 0;
}