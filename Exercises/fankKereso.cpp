/*
Találja meg az összes fánkot a fank.jpg képen, 
majd egyesével mentse le a fánkokat tartalmazó képrészleteket (befoglaló téglalap által megadott rész) egy mappába.
*/



#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat fank = imread("Kepek/fank.jpg", IMREAD_COLOR);
	Mat bin;

	vector<Mat> chs;
	split(fank, chs);
	Mat img = chs[1];

	threshold(img, bin, 130, 255, THRESH_BINARY);
	Mat blured;
	medianBlur(bin, blured, 3);

	Mat S = getStructuringElement(MORPH_ELLIPSE, Size(27, 27));
	Mat dilated;
	dilate(blured, dilated, S);


	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(dilated, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int count = 0;
	vector<Mat> fankok(contours.size());
	for (int i = 0; i < contours.size(); ++i)
	{
		Rect box = boundingRect(contours[i]);
		fankok[i] = Mat::zeros(box.size(), CV_8UC3);
		fankok[i] = fank(box);
		//drawContours(fank, contours, i, Scalar(0, 255, 0), 3);
		//rectangle(fankok[i], box, Scalar(0, 0, 255)); // hogy ne legyen rajtuk a piros keret, csupan szemleltetesbol volt itt
		imwrite("Kepek/fank" + to_string(i) + ".jpg", fankok[i]);	// lementi az osszes fankot, ami a kepunkon van!
	}

	return 0;
}