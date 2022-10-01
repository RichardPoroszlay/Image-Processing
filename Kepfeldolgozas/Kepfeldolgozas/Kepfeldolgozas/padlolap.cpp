#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;

void convert(const cv::Mat src, cv::Mat& dest) {
	Mat srcf;
	src.convertTo(srcf, CV_32FC3, 1/255.0);
	cvtColor(srcf, dest, cv::COLOR_BGR2Lab);
}

double lab_diff(const cv::Mat lab1, const cv::Mat lab2) {
	Mat diff = lab1 - lab2;
	Mat diff2 = diff.mul(diff);
	vector<Mat> chs;
	split(diff2, chs); // dL da db külön csatornán (elsõ d jelenti a deltát)
	Mat E;
	cv::sqrt(chs[0] + chs[1] + chs[2], E);

	return cv::mean(E)[0];
	
}



int main() {
	/*
		Mat etalon = cv::imread("C:/padlolapok/etalon.png", IMREAD_COLOR);

		imshow("etalon", etalon);

		Mat img;
		for (int i = 1; i <= 7; ++i) {
			img = cv::imread("C:/padlolapok/fa_" + std::to_string(i) + ".png");
			string ablaknev = "img_" + std::to_string(i);
			imshow(ablaknev, img);
			moveWindow(ablaknev, 200, 10 + i * 60);

		}
	*/
	
	/*
		Mat etalon = cv::imread("C:/padlolapok/etalon.png", IMREAD_COLOR);
		Mat elab;
		convert(etalon, elab);
		imshow("etalon", etalon);

		Mat img, ilab;
		for (int i = 1; i <= 7; ++i) {
			img = cv::imread("C:/padlolapok/fa_" + std::to_string(i) + ".png");
			convert(img, ilab);
			double E = lab_diff(elab, ilab);
			cout << i << " " << E << '\n';
			string ablaknev = "img_" + std::to_string(i);
			imshow(ablaknev, img);
			moveWindow(ablaknev, 200, 10 + i * 60);

		}
	*/

	waitKey();
	return 0;
}
