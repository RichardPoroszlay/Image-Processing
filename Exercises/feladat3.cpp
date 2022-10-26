/*
1. Olvassa be valamelyik gombot tartalmazó képet.
2. Küszöbölje a képet úgy, hogy az eredménykép fekete - fehér legyen.A gomb legyen az elõtér. 
	A küszöbértéket konstans értékkel adja meg.
3. Mentse el az eredményt result.png néven.
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
