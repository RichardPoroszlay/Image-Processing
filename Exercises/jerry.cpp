/*
	1. Nyissa meg a snow.avi videót. 
    2. Olvassa be a jerry_monent képet. 
    3. Minden egyes képkockára hajtsa végre az alábbi mûveleteket:
        - másolja rá Jerry-t (természetesen a háttér nélkül). Jele a videó jobb oldalára. 
        - várakoztasson 20 milliszekundumot. 
    4. Az utolsó képkocka bezárása elõtt várakozzon addig, amíg a felhasználó le nem üt egy billentyût. 
*/


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat jerry = imread("Kepek/jerry_moment.jpg", IMREAD_COLOR);
	Mat hsv;
	cvtColor(jerry, hsv, COLOR_BGR2HSV);

	Mat kivagott = Mat::zeros(jerry.size(), CV_8UC3);
	int saturation;
	for (int i = 0; i < hsv.rows; i++) {
		for (int j = 0; j < hsv.cols; j++) {
			saturation = hsv.at<Vec3b>(i, j)[1];
			if (saturation < 220)
				kivagott.at<Vec3b>(i, j) = jerry.at<Vec3b>(i, j);
		}
	}
	Mat bin2, dil;
	Mat gray;
	cvtColor(kivagott, gray, COLOR_BGR2GRAY);
	threshold(gray, bin2, 1, 255, THRESH_BINARY);
	Mat S4 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	dilate(bin2, dil, S4);

	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(dil, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Rect box = boundingRect(contours[0]);
	Mat szukenvagottJerry = kivagott(box);


	Mat blured, kicsinyitettJerry;
	medianBlur(szukenvagottJerry, blured, 5);
	resize(szukenvagottJerry, kicsinyitettJerry, szukenvagottJerry.size() / 2);


	// sasra rarakas
	// video betoltese es a sas kiemelese
	VideoCapture cap;
	cap.open("Kepek/snow.avi");

	// ellenorzes vegett
	if (!cap.isOpened())
	{
		cout << "Hiba!" << endl;
		exit(-1);
	}

	Mat img, dest;
	bool kimentett = false;
	constexpr int rowOffset = 10, colOffset = 10;
	while (cv::waitKey(20) != 'q')
	{
		cap >> img;
		if (img.empty()) {
			cerr << "A kepkockat nem lehetett megjeleniteni!" << endl;
			break;
		}

		// egy kepkocka kimentese
		if (!kimentett) {
			imwrite("Q4AFYK.png", img);
			kimentett = true;
		}

		// jobb felso sarokba masolas
		for (int i = 0 + rowOffset, m = 0; i < img.rows - kicsinyitettJerry.rows, m < kicsinyitettJerry.rows; ++i, ++m) {
			for (int j = img.cols - kicsinyitettJerry.cols - colOffset, n = 0; j < img.cols, n < kicsinyitettJerry.cols; ++j, ++n) {
				Vec3b pont = kicsinyitettJerry.at<Vec3b>(m, n);
				if (pont[0] > 5 && pont[1] > 5 && pont[2] > 5)
					img.at<Vec3b>(i, j) = pont;
			}
		}

		// itt nem ertem hogy a kesz kepet, vagy csak Jerryt kell blure-ozni
		Mat blured;
		GaussianBlur(img, blured, Size(5, 5), 1.4);
		imshow("Q4AFYK", blured);
		waitKey(20);
	}


    return 0;
}