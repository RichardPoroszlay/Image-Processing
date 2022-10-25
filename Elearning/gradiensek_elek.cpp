/*
OpenCV segadanyagok:
Gradiens szamitas, gradiens erossegen alapulo eldetektals.
*/

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. fuggvenyek

using namespace std;
using namespace cv;

void roberts(const Mat img, Mat& dest) {
	Mat tmp = Mat::zeros(img.size(), CV_16S);

	// ezzel megsporolhato a .at<uchar> resz kiirasa a pixelertekek lekeresekor
	Mat_<uchar> img2 = (Mat_<uchar>)img;

	for (int i = 0; i < img.rows - 1; ++i) {
		for (int j = 0; j < img.cols - 1; ++j) {
			//a b
			//c d
			//gradiens errosseg kozelitese: |a-d| + |b-c|
			tmp.at<short>(i, j) = fabs(img2(i, j) - img2(i + 1, j + 1)) + fabs(img2(i, j + 1) - img2(i + 1, j));
		}
	}
	//a lathatosag es a kompaktabb tarolas erdekeben visszaterunk a szokasos vilagba
	convertScaleAbs(tmp, dest);

	//egyebken egy pici szorzassal is meg lehetne oldani, hogy lathato legyen az eredmeny
	//a kozepszurke ebben az esetben a 0-t jelenti, mert elojeles tipusunk (CV_16S, short) van.
	//dest = tmp.clone()*255;
}

/// <summary>
/// Gradiens erosseg kozelitese 
/// </summary>
/// <param name="img"></param>
/// <param name="dest"></param>
void sobel_approx(const Mat img, Mat& dest) {
	Mat gx, gy, tmp;
	Sobel(img, gx, CV_16S, 1, 0);
	Sobel(img, gy, CV_16S, 0, 1);
	tmp = cv::abs(gx) + cv::abs(gy);
	convertScaleAbs(tmp, dest);
}

/// <summary>
/// Gradiens erosseg szamitasa
/// Eroforrasigenyesebb, mint a kozelites, ezert sokkal ritkabban hasznaljuk.
/// </summary>
/// <param name="img"></param>
/// <param name="dest"></param>
void sobel(const Mat img, Mat& dest) {
	Mat gx, gy, tmp;
	// a gyokvonas miatt float-ot hasznalunk a tarolasra!
	Sobel(img, gx, CV_32F, 1, 0);
	Sobel(img, gy, CV_32F, 0, 1);
	cv::sqrt(gx.mul(gx) + gy.mul(gy), tmp);
	convertScaleAbs(tmp, dest);
}

int main() {
	//bekerunk egy kepet a sorozatban szereplo kepek meretenek megismeresehez
	Mat img = imread("doggo.jpg", IMREAD_GRAYSCALE);

	Mat dest_roberts;
	roberts(img, dest_roberts);

	Mat dest_sobel_approx;
	sobel(img, dest_sobel_approx);

	Mat dest_sobel;
	sobel(img, dest_sobel);

	Mat dest_laplace;
	Laplacian(img, dest_laplace, CV_8UC1, 3);

	imshow("eredeti", img);
	imshow("roberts", dest_roberts);
	imshow("sobel_approx", dest_sobel_approx);
	imshow("sobel", dest_sobel);
	imshow("laplacian", dest_laplace);

	waitKey(0);

	// egesz jonak tunik, de nezzuk mi a helyzet valojaban:
	// a zajos kep azt jelenti, hogy meg 50-es erossegu hamis elek is vannak a kepen
	// termeszetesen emelheto a hatar tovabb, es egyre kevesebb zaj marad
	// de vigyazz, mert ha tul sokaig emeled, akkor a valodi elek is odavesznek
	// Jo ha tudod: sok kep eseteben nem fogsz megfelelo hatart talalni! 
			//(kapcsolodo temak: zajszures, konturkovetes)
	int kuszob = 50;

	// a zaj es a valodi elek elvalasztasa kuszobolessel 
	// a hatar mindig problemafuggo, a megtalalasa sokszor nem trivialis
	// konnyen megszakadhatnak az elek (megoldas: konturkovetes: ld. Canny)
	threshold(dest_roberts, dest_roberts, kuszob, 255, THRESH_BINARY);
	imshow("elek: roberts + threshold", dest_roberts);

	threshold(dest_sobel_approx, dest_sobel_approx, kuszob, 255, THRESH_BINARY);
	imshow("elek: sobel_approx + threshold", dest_sobel_approx);

	threshold(dest_sobel, dest_sobel, kuszob, 255, THRESH_BINARY);
	imshow("elek: sobel + threshold", dest_sobel);

	threshold(dest_laplace, dest_laplace, kuszob, 255, THRESH_BINARY);
	imshow("elek: roberts + threshold", dest_laplace);

	waitKey(0);

	return 0;
}