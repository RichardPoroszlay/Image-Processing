/*
Tal�lja meg a k�pen a k�kuszos f�nkokat a fank.jpg, majd rajzolja �ket k�rbe 3 pixel vastag fekete vonallal. Jelen�tse meg az eredm�nyt. 
(Megj. Nem elv�rt a fekete vonal prec�z illeszked�se. )
*/




#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {

	Mat fank = imread("Kepek/fank.jpg", IMREAD_COLOR);

	vector<Mat> chs;
	split(fank, chs);
	Mat img = chs[1];

	Mat bin, dilated, blured;
	Mat S = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	dilate(img, dilated, S);
	medianBlur(dilated, blured, 7);

	threshold(blured, bin, 227, 255, THRESH_BINARY);
	Mat dilated2;
	Mat S2 = getStructuringElement(MORPH_ELLIPSE, Size(19, 19));
	dilate(bin, dilated2, S2);

	Mat S3 = getStructuringElement(MORPH_ELLIPSE, Size(17, 17));
	Mat eroded, blured2;
	erode(dilated2, eroded, S3);
	medianBlur(eroded, blured2, 19);

	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(blured2, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int count = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		double terulet = contourArea(contours[i]);
		if (terulet > 1000) {
			//cout << i << ". terulet = " << terulet << endl;
			drawContours(fank, contours, i, Scalar(0, 0, 0), 3);
			count++;
		}
	}
	cout << "|||||||||||||||||||| Ennyi kokuszos fank tallahato a kepen: " << count << endl;

	imshow("bin", fank);
	waitKey(0);


	return 0;
}