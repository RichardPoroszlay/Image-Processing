/*
	1. Olvassa be a gombokat tartalmazó képet.
	2. Küszöbölje a képet. (A fehér gombok elveszhetnek.)
	3. Határozza meg a képen a többi gomb külsõ kontúrját.
	4. Rajzolja ki a kontúrokat eltérõ színnel a gombokat tartalmazó képre.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void getContours(Mat imgDil, Mat img) {
	
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
	
		findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		// drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	
		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
	
		for (int i = 0; i < contours.size(); i++)
		{
			int area = contourArea(contours[i]);
			cout << area << endl;
			string objectType;
	
			if (area > 1000)
			{
				float peri = arcLength(contours[i], true);	// perimeter
				approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
				cout << conPoly[i].size() << endl;	// prints out the number of points/edges/corner points
				boundRect[i] = boundingRect(conPoly[i]);
	
				int objCor = (int)conPoly[i].size();
	
				if (objCor == 3) { objectType = "Tri"; }
				else if (objCor == 4)
				{
					float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
					cout << aspRatio << endl;
					if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
					else { objectType = "Rect"; }
				}
				else if (objCor > 4) { objectType = "Circle"; }
	
				drawContours(img, conPoly, i, Scalar(250, 10, 0), 5);
				// rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
				putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
			}
	}
}


// detektálja a széleket, viszont nem különbözõ színekkel rajzolja körbe
int main() {

	Mat img = imread("Kepek/color_buttons.jpg");
	
	Mat kuszobolt;
	threshold(img, kuszobolt, 100, 255, THRESH_BINARY);

	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;


	cvtColor(kuszobolt, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	
	getContours(imgDil, kuszobolt);

	imshow("kuszobolt", kuszobolt);
	// imshow("img", img);
	waitKey();


	return 0;
}