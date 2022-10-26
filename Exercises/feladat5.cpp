///*
//1. Olvassa be valamelyik gombot tartalmaz� k�pet sz�rkesk�l�ban.
//2. M�retezze �t a k�pet az eredeti m�ret�nek dupl�j�ra.
//3. Alkalmazzon speci�lis k�sz�b�l�st, mely meg�rzi az el�teret, a h�tt�rpontokat viszont kinull�zza("t�rli").
//4. Jelen�tse meg az eredm�nyt.
//*/
//
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("Kepek/color_button1.jpg", IMREAD_GRAYSCALE);
	Mat resized;
	resize(img, resized, Size(), 2, 2);

	Mat mask;
	inRange(resized, 70, 234, mask);
	medianBlur(mask, mask, 7);

	resized.setTo(0, 255 - mask);

	imshow("Eredmeny", resized);

	waitKey();

	return 0;
}