/*
* 9. feladat
	1. Olvassa be az egyik gombot tartalmazó képet.
	2. Küszöbölje a képet.
	3. Határozza meg a képen a gomb külsõ kontúrját.
	4. Jelenítse meg a konzolon a kontúr területe és a fehér pontok száma közti különbséget.

* 10.k feladat
    1. Olvassa be az egyik gombot tartalmazó képet.
    2. Küszöbölje a képet. 
    3. Határozza meg a képen a gomb összes kontúrját.
    4. Rajzolja ki különbözõ színnel a gomblyukakat.
    5. Jelenítse meg a képet.

* 11.k feladat
	1. Olvassa be a gombokat tartalmazó képet.
    2. Küszöbölje a képet (a fehér gombok elveszhetnek)
    3. Határozza meg a képen a gombok minden kontúrját.
    4. Számolja össze, hogy hány gomblyuk van a képen és jelenítse meg az eredményt a standard outputon.
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