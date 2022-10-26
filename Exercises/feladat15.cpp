/*
	1. Olvassa be a gombokat tartalmaz� k�pet.
	2. K�sz�b�lje a k�pet(a feh�r gombok elveszhetnek)
	3. Hat�rozza meg a gombok k�ls� kont�rj�t.
	4. J�rja be a kont�r vektort :
		- Hat�rozza meg a kont�r befoglal� t�glalapj�t
		- V�gja ki a t�glalap �ltal megadott r�szt az eredeti k�pr�l
		- A kapott k�peket jelen�tse meg �s v�rakoztasson 20 ms - ig.
*/

#include <iostream>
#include <string>
#include <vector>
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
	vector<Rect> boxes;
	vector<Mat> boxImgs;
	for (int i = 0; i < contours.size(); ++i)
	{
		boxes.push_back(boundingRect(contours[i]));
		boxImgs.push_back(Mat::zeros(Size(boxes[i].width, boxes[i].height), CV_8UC3));

		cout << i << "-ik teglalap magassaga: " << boxes[i].height << " es a szelessege: " << boxes[i].width << endl;
		drawContours(src, contours, i, Scalar(255, 0, 0), 1);
		rectangle(src, boxes[i], Scalar(0, 0, 255));

		boxImgs[i] = src(boxes[i]);
	}


	for (int i = 0; i < boxImgs.size(); ++i) {
		imshow("asd", boxImgs[i]);
		waitKey(1000);
	}

	return 0;
}
