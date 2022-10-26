/*
* 9. feladat
	1. Olvassa be az egyik gombot tartalmaz� k�pet.
	2. K�sz�b�lje a k�pet.
	3. Hat�rozza meg a k�pen a gomb k�ls� kont�rj�t.
	4. Jelen�tse meg a konzolon a kont�r ter�lete �s a feh�r pontok sz�ma k�zti k�l�nbs�get.

* 10.k feladat
    1. Olvassa be az egyik gombot tartalmaz� k�pet.
    2. K�sz�b�lje a k�pet. 
    3. Hat�rozza meg a k�pen a gomb �sszes kont�rj�t.
    4. Rajzolja ki k�l�nb�z� sz�nnel a gomblyukakat.
    5. Jelen�tse meg a k�pet.

* 11.k feladat
	1. Olvassa be a gombokat tartalmaz� k�pet.
    2. K�sz�b�lje a k�pet (a feh�r gombok elveszhetnek)
    3. Hat�rozza meg a k�pen a gombok minden kont�rj�t.
    4. Sz�molja �ssze, hogy h�ny gomblyuk van a k�pen �s jelen�tse meg az eredm�nyt a standard outputon.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat rgb = imread("Kepek/color_button1.jpg", IMREAD_COLOR);
	Mat binary, blured, gray;
	cvtColor(rgb, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 128, 255, THRESH_BINARY_INV);
	medianBlur(binary, blured, 5);
	Mat S = getStructuringElement(MORPH_CROSS, Size(7, 7));
	dilate(binary, binary, S);

	imshow("binary blured", blured);


	// mivel egy kontur szamos pontbol all es tobb kontur is lehet
	vector<vector<Point>> contours; // ebben taroljunk a konturokat


	vector<Vec4i> hier; // 4 ertekes integer
	findContours(binary, contours, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);

	int gombCount = 0, kisGombCount = 0;
	double kulsoTerulet = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		if (hier[i][3] == -1) // nincs szulo, vagyis a legkulso kontur
		{
			drawContours(rgb, contours, i, Scalar(255, 0, 0), 2);
			gombCount++;
			kulsoTerulet += contourArea(contours[i]);
		}
		else {
			drawContours(rgb, contours, i, Scalar(0, 255, 0), 2);
			kisGombCount++;
		}

	}

	cout << "|||||||||||||||||| A gomb terulete: " << kulsoTerulet << endl;
	cout << "|||||||||||||||||| A kisgombok szama: " << kisGombCount << endl;
	cout << "|||||||||||||||||| Ezek kulonbsege: " << kulsoTerulet - kisGombCount << endl;

	imshow("rgb", rgb);
	waitKey(0);

	return 0;
}