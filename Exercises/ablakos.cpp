/*
 �rjon programot, mely beolvassa az ablakok.jpg k�pet �s megsz�molja, hogy h�ny ablakb�l �rad ki a f�ny.
 �gyeljen r�, hogy a keretek miatt ne sz�moljon egy ablakot t�bbsz�r.
 Rajzolja is k�rbe a vil�gosnak v�lt ablakokat, hogy az eredm�nyt r�n�z�sre is ellen�rizni lehessen.
*/


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat ablakok = imread("Kepek/ablakok.jpg", IMREAD_COLOR);
	Mat gray, bin;
	cvtColor(ablakok, gray, COLOR_BGR2GRAY);

	threshold(gray, bin, 60, 255, THRESH_BINARY);

	Mat S = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat dilated, blured;
	dilate(bin, dilated, S);
	medianBlur(dilated, blured, 17);


	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(blured, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int count = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		drawContours(ablakok, contours, i, Scalar(0, 255, 0), 2);
		count++;
	}

	cout << "||||||||||||||||||| Ennyi ablak van a kepen: " << count << endl;

	imshow("eredmeny", ablakok);
	waitKey(0);


	return 0;
}