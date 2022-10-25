/**
* OpenCV gyakorlat
* Hough kordetektalo
	- a Canny detektalora epit, ezert erdemes lehet elobb a canny eldetektalot magaban futtatni a kepre, hogy a kuszoberteket beallitsd
	- ha ismert a kor merete, feltetlenul hasznald ki, mert jelentosen gyorsit
	- ha nem ad vissza kort, lazits a parametereken, elofordulhat, hogy mas tulajdonsagok alapjan, utolag kell majd szurni a megfelelo koroket
*/

#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

/// <summary>
/// Sobelre epit
/// </summary>
/// <param name="gray"></param>
/// <param name="circles"></param>
void kordetektalo1(const Mat& gray, vector<Vec3f>& circles) {

	int cannyTh = 80;  // biztos el hatara a Canny detektornak
	int minPoints = 50; // hany eloterponton kell atmennia a korvonalnak
	int minR = 22;  //minimalis sugar
	int maxR = 26;  //maximalis sugar
	int d = 2; //felbontast osztja (1-> eredeti, 2 -> 2x2-es resz egy 'doboz', stb)  
	int minDist = 10; //a minR-nel kozelebb korokbol az erosebbet kerjuk

	//vector<Vec3f> circles; // Vec3f: [0]: kozeppont x,  [1] kozeppont y, [2] subar
	cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, d, minDist, cannyTh, minPoints, minR, maxR);
}

/// <summary>
/// Scharr elkeresore epit (pontosabban becsulheto az el irany es erosseg)
/// </summary>
/// <param name="gray"></param>
/// <param name="circles"></param>
void kordetektalo2(const Mat& gray, vector<Vec3f>& circles) {
	int cannyTh = 80;  // biztos el hatara a Canny detektornak, de Sobel helyett Scharr operatort hasznal
	double perfectness = 0.70; // mennyire legyen tokeletes kor
	int minR = 20;  //minimalis sugar
	int maxR = 28;  //maximalis sugar
	int d = 1; //felbontast osztja (1-> eredeti, 2 -> 2x2-es resz egy 'doboz', stb)  
	int minDist = 10; //a minR-nel kozelebb korokbol az erosebbet kerjuk

	//vector<Vec3f> circles; // Vec3f: [0]: kozeppont x,  [1] kozeppont y, [2] subar
	cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT_ALT, d, minDist, cannyTh, perfectness, minR, maxR);
}


int main() {

	Mat colorImg = imread("go2.png");

	assert(!colorImg.empty());

	Mat gray;
	cvtColor(colorImg, gray, COLOR_BGR2GRAY);

	vector<Vec3f> circles; // Vec3f: [0]: kozeppont x,  [1] kozeppont y, [2] subar
	kordetektalo1(gray, circles);
	//kordetektalo2(gray, circles);


	//Korok kirajzolasa
	Scalar feketebabu(0, 0, 255);
	Scalar feherbabu(0, 255, 0);
	Scalar hamis(128, 128, 128);
	int x, y, r;

	for (auto c : circles) {
		x = c[0];
		y = c[1];
		r = c[2];
		if (gray.at<uchar>(y, x) < 50)
			circle(colorImg, Point(x, y), r, feketebabu, 2);
		else if (gray.at<uchar>(y, x) > 150)
			circle(colorImg, Point(x, y), r, feherbabu, 2);
		else //nem is feher, nem is fekete, utolag is kidobhato a korok kozol, ami nem kell
			 //szukseg is lehet ra, ha nem talalunk olyan parametereket, ami tokeletes eredmenyt ad
			circle(colorImg, Point(x, y), r, hamis, 2);
	}


	imshow("babuk", colorImg);
	waitKey(0);

	return 0;
}