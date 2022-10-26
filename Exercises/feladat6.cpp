/*
	1. Olvassa be a két képet, ami egy - egy gombot tartalmaz.
	2. Mossa el mindkét gombot egy 7x7 - es mediánszûrõvel.
	3. Konvertálja a képeket valóssá.
	4. Váltsa át mindkét képet Lab színtérbe.
	5. Számítsa ki, hogy mennyi a két kép középpontjai között a teljes színkülönbség. Az eredményt(egy valós szám) a standard outputra írja ki.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void convert_labf(const Mat rgb, Mat& dest) {
	Mat rgbf;
	rgb.convertTo(rgbf, CV_32FC3, 1 / 255.0);

	// Az elozo atalakitas miatt a dest kep is CV_32FC3-as lesz, 
	//ami a kesobbi szamitasok miatt erdekes
	cvtColor(rgbf, dest, COLOR_BGR2Lab);
}

string category(double diff) {
	if (diff < 0.5)
		return "Szemre nem erzekelheto.";

	if (diff < 1.5)
		return "Alig erzekelheto.";

	if (diff < 3.0)
		return "Erzekelheto.";

	if (diff < 6.0)
		return "Jol lathato.";

	return "Nagy szininger kulonbseg.";
}

int main() {
	Mat img1 = imread("Kepek/color_button1.jpg");
	Mat img2 = imread("Kepek/color_button2.jpg");

	

	Mat blurIMG1;
	Mat blurIMG2;
	medianBlur(img1, blurIMG1, 7);
	medianBlur(img2, blurIMG2, 7);

	Mat lab1;
	Mat lab2;
	convert_labf(blurIMG1, lab1);
	convert_labf(blurIMG2, lab2);

	// különbség kiszámítása
	double L1, L2, a1, a2, b1, b2;
	L1 = lab1.at<Vec3f>((int)lab1.rows / 2, (int)lab1.cols / 2)[0];
	L2 = lab2.at<Vec3f>((int)lab2.rows / 2, (int)lab2.cols / 2)[0];

	a1 = lab1.at<Vec3f>((int)lab1.rows / 2, (int)lab1.cols / 2)[1];
	a2 = lab2.at<Vec3f>((int)lab2.rows / 2, (int)lab2.cols / 2)[1];

	b1 = lab1.at<Vec3f>((int)lab1.rows / 2, (int)lab1.cols / 2)[2];
	b2 = lab2.at<Vec3f>((int)lab2.rows / 2, (int)lab2.cols / 2)[2];

	double deltaE;
	deltaE = sqrt((L2 - L1) * (L2 - L1) + (a2 - a1) * (a2 - a1) + (b2 - b1) * (b2 - b1));
	cout << "|||||||||||||||||||||||||||| The difference is: " << deltaE << endl;

	imshow("Img1", img1);
	imshow("Img2", img2);
	imshow("BlurIMG1", blurIMG1);
	imshow("BlurIMG2", blurIMG2);
	imshow("Lab1", lab1);
	imshow("Lab2", lab2);
	waitKey();

	return 0;
}

