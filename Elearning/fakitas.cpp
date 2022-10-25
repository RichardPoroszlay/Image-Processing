#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void vilagosit1(Mat img) { //Miért változik az eredeti kép? Válasz: mivel azt módosítjuk, nem egy referenciát
	img = img + 100;
}
void vilagosit2(Mat img, Mat& dest) { //Miért kell az & jel? Válasz: mert referencia
	dest = img + 100;
}

int main() {

	Mat img = cv::imread("doggo.jpg", IMREAD_GRAYSCALE);

	vilagosit1(img);
	imshow("fako1", img);

	Mat dest; // A kép még üres
	vilagosit2(img, dest);
	imshow("fako2", dest);

	waitKey();
	return 0;
}