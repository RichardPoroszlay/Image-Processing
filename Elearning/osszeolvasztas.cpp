//
// Ket kep "osszeolvasztasa". Mind a ketto latszani fog valamennyire.  
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat fg = cv::imread("kurama.jpg");
	Mat bg = cv::imread("background.jpg");

	// ures-e?
	if (fg.empty() || bg.empty()) {
		cout << "Upsz" << endl;
		exit(-1);
	}

	Mat bg2;
	resize(bg, bg2, fg.size());

	double a = 0.5;  // valtoztasd, es figyeld meg a hatast
	Mat u = (1 - a) * bg2 + a * fg;

	imshow("eloter", fg);
	imshow("hatter (atmeretezve)", bg2);
	imshow("eredmeny", u);

	waitKey();
	return 0;
}