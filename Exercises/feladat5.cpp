///*
//1. Olvassa be valamelyik gombot tartalmazó képet szürkeskálában.
//2. Méretezze át a képet az eredeti méretének duplájára.
//3. Alkalmazzon speciális küszöbölést, mely megõrzi az elõteret, a háttérpontokat viszont kinullázza("törli").
//4. Jelenítse meg az eredményt.
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