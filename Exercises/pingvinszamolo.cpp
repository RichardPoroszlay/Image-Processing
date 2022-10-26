/*
Olvassa be a pinguen_colony2.png k�pet �s hat�rozza meg, hogy h�ny pingvin van a k�pen. 
Jel�lj�n meg minden pingvint k�rrel vagy m�s jel�l�vel, 
hogy r�n�z�sre is ellen�rizni lehessen a program helyess�g�t.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("Kepek/pinguen_colony2.png", IMREAD_COLOR);
	Mat gray, bin;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// csuszkak letrehozasa
	//string menu = "tool";
	//cv::namedWindow(menu, WINDOW_NORMAL);
	//cv::resizeWindow(menu, Size(500, 50));

	//int thresh = 0;

	//createTrackbar("thresh", menu, &thresh, 255);

	threshold(gray, bin, 55, 255, THRESH_BINARY_INV);
	Mat S = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	Mat eroded, blured;
	erode(bin, eroded, S);
	medianBlur(eroded, blured, 5);

	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(blured, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int count = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		drawContours(img, contours, i, Scalar(0, 255, 0), 2);
		count++;
	}

	cout << "||||||||||||||||||| Ennyi pingvin van a kepen: " << count << endl;

	//imshow("eroded", blured);
	imshow("eredeti", img);
	waitKey(0);


	return 0;
}