/*
	1. Olvassa be a gombokat tartalmaz� k�pet.
	2. K�sz�b�lje a k�pet(a feh�r gombok elveszhetnek)
	3. Hat�rozza meg a gombok k�ls� kont�rj�t.
	4. Hat�rozza meg az egyes gombok magass�g�t �s sz�less�g�t a befoglal� t�glalapjuk alapj�n.
	5. Az �rt�keket a standard outputra �rja ki vagy �rja r� a k�pre.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {

	Mat src = imread("Kepek/color_buttons.jpg", IMREAD_COLOR); // 3 csatornas kep alapbol
	Mat gray, blur_img, thresh_img;

	//convert to grayscale
	cvtColor(src, gray, COLOR_BGR2GRAY);

	//bluring
	blur(gray, blur_img, Size(3, 3));

	// thresholding
	threshold(blur_img, thresh_img, 160, 255, THRESH_BINARY_INV);

	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(thresh_img, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector< vector<Point> > hull(contours.size());
	for (int i = 0; i < contours.size(); ++i)
	{
		Rect box = boundingRect(contours[i]);
		cout << i << "-ik teglalap magassaga: " << box.height << " es a szelessege: " << box.width << endl;
		drawContours(src, contours, i, Scalar(255, 0, 0), 1);
		rectangle(src, box, Scalar(0, 0, 255));
	}


	imshow("binary thresholded blured image", thresh_img);
	imshow("rgb", src);
	waitKey(0);


	return 0;
}