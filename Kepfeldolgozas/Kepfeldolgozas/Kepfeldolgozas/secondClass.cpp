// Second Class

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;


// Below are functions for different purposes

// enlightens a picture
void vilagosit1(Mat& img) { 
	img = Mat::zeros(100,100,CV_8UC1);

}

// inverts a picutre
void invertal(Mat img, Mat& dest) { // Ezzel a függvénnyel invertáljuk a paraméterül adott képet
	dest = Scalar(255,255,255)-img;
}



void eloterMasolo(const cv::Mat fg, cv::Mat& bg) {
	resize(bg, bg,fg.size());

	Vec3b feher(255, 255, 255);
	for (int i = 0; i < fg.rows; ++i) {
		for (int j = 0; j < fg.cols; ++j) {
			Vec3b c = fg.at<Vec3b>(i, j);
			// if (feher != c) {
			if(c[0] < 245 || c[1] < 245 || c[2] < 245) {

				bg.at<Vec3b>(i, j) = c;
			}
		}
	}
}


void narancsmasolo(const cv::Mat src, cv::Mat& dest) {
	dest.create(src.size(), CV_8UC1);
	dest.setTo(0);

	Mat mask;
	inRange(src, Scalar(0,0,150), Scalar(200,200,255), mask);

	src.copyTo(dest, mask);

	
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			Vec3b c = src.at<Vec3b>(i, j);
			// if (feher != c) {
			if (c[2] > c[0] && c[2] > c[1]) {	// R - c[2]

				dest.at<Vec3b>(i, j) = c;
			}
		}
	}
	 
}


int main() {
	
/*
	// Conflating two pictures

	Mat r = cv::imread("C:/kurama.jpg", IMREAD_COLOR);
	Mat h = cv::imread("C:/background.jpg", IMREAD_COLOR);
	
	if (r.empty() || h.empty()) {
		cout << "Picture is missing!" << '\n';
		exit(-1);
	}
	Mat h2;
	resize(h, h2, r.size());

	double a = 0.5; // this controls the pictures display intensity
	Mat u = a * r + (1 - a) * h2;	// with this expression the pictures will be conflated

	imshow("hatter", h2);
	imshow("rajz", r);
	imshow("eredmeny", u);
	
	waitKey();
	return 0;
*/
	

/*
	// Two pictures will appear, but they will be colored differently
	
	Mat img = cv::imread("C:/doggo.png", IMREAD_GRAYSCALE);
	if (img.empty()) {
		cout << "Picture is missing!" << '\n';
		exit(-1);
	}

	imshow("original", img);	

	Mat dest; // The picture is empty yet
	invertal(img, dest);
	imshow("pale2", dest);	// Paler picture will be displayed

	waitKey();
	return 0;
*/


/*
	// Coloring a 2x3 matrix

	Mat m(2, 3, CV_8UC3); // creating a 3chanel picture
		
	//Mat_<Vec3b> m(2, 3);
	namedWindow("sample", WINDOW_NORMAL); // resizable window
	resizeWindow("sample", 1200, 800); // zoom
	
	m.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);
	m.at<Vec3b>(0, 1) = Vec3b(0, 255, 0);
	m.at<Vec3b>(0, 2) = Vec3b(255, 0, 0);
	m.at<Vec3b>(1, 0) = Vec3b(0, 0, 0);
	m.at<Vec3b>(1, 1) = Vec3b(39, 127, 255);
	m.at<Vec3b>(1, 2) = Vec3b(0, 255, 255);
	cout << m << '\n';

	imshow("sample", m); // display
	waitKey();
	return 0;
*/


/*
	// the non-white points of an image are copied onto another image
	Mat r = cv::imread("C:/kurama.jpg", IMREAD_COLOR);
	Mat h = cv::imread("C:/background.jpg", IMREAD_COLOR);
	
	imshow("drawing", r);
	imshow("background", h);
	eloterMasolo(r, h);
	imshow("result", h);

	waitKey();
	return 0;
*/


/*
	Mat narancs = cv::imread("C:/orange1.jpg", IMREAD_COLOR);
	Mat dest;
	
	imshow("orange", narancs);
	narancsmasolo(narancs, dest);
	imshow("result", dest);

	
	waitKey();
	return 0;
*/	

}
