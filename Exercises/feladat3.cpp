/*
1. Olvassa be valamelyik gombot tartalmaz� k�pet.
2. K�sz�b�lje a k�pet �gy, hogy az eredm�nyk�p fekete - feh�r legyen.A gomb legyen az el�t�r. 
	A k�sz�b�rt�ket konstans �rt�kkel adja meg.
3. Mentse el az eredm�nyt result.png n�ven.
*/



#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void main() {

	Mat img = imread("Kepek/color_button1.jpg", IMREAD_GRAYSCALE);

	if (img.empty()) {
		cout << "Image not found" << '\n';
		exit(-1);
	}

	Mat dest;
	threshold(img, dest, 100, 255, THRESH_BINARY);

	medianBlur(dest, dest, 5);
	imshow("kuszobolt", dest);

	imwrite("result.png", dest);
	
	waitKey(0);
		
}
