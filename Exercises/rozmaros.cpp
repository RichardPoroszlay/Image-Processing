/*
	Becsülje meg a napozó rozmárok számát az agyarak száma alapján.

	1. Olvassa be a walrus_jeff_foot.png képet.
	2. Küszöbölje a kék csatorna alapján (ne sajnálja az idõt a megfelelõ küszöbérték megkeresésére)
	3. A külsõ körvonalakat gyûjtse össze a küszöbölt képen.
	4. Minden körvonalra:
		- határozza meg a minimális befoglaló téglalapot az alábbi függvény segítségével:
			cv::RotatedRect minAreaRect(cv::InputArray points);
		- ha a kapott téglalap hosszabbik oldala legalább kétszer olyan hosszú, mint a rövidebb oldal, akkor az adott kontúrt tekintse rozmáragyarnak, növeljen egy számlálót és rajzolja ki zölddel a kontúrt.  
			Egyébként rajzolja ki kékkel a kontúrt az eredeti képre. 
			Megj.: Szükség esetén (pl.: ha a küszöbölése nem az igazi) a kontúr területe/kerülete alapján is kidobhat kontúrokat ennél a lépésnél. 

	5. Írja ki a rozmárok becsült számát (normál esetben egy rozmár 2 agyarral bír). 
*/


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;



int main() {

	Mat walrus = imread("Kepek/walrus_jeff_foott.png", IMREAD_COLOR);
	vector<Mat> chs;
	split(walrus, chs);

	imshow("ch0", chs[0]);

	Mat bin;
	threshold(chs[0], bin, 188, 255, THRESH_BINARY);
	Mat S = getStructuringElement(MORPH_CROSS, Size(1, 1));
	Mat eroded, blured;
	erode(bin, eroded, S);
	medianBlur(eroded, blured, 1);

	// finding contours
	vector<vector<Point>> contours;
	vector<Vec4i> hier;
	findContours(blured, contours, hier, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int count = 0;
	for (int i = 0; i < contours.size(); ++i)
	{
		RotatedRect rect;
		rect = minAreaRect(contours[i]);

		int hosszabbik, rovidebbik;
		if (rect.size.width >= rect.size.height)
		{
			hosszabbik = rect.size.width;
			rovidebbik = rect.size.height;
		}
		else {
			hosszabbik = rect.size.height;
			rovidebbik = rect.size.width;
		}

		if (hosszabbik >= rovidebbik * 2) {
			drawContours(walrus, contours, i, Scalar(0, 255, 0), 1);
			count++;
		}
		else drawContours(walrus, contours, i, Scalar(255, 0, 0), 1);

		//rectangle(walrus, rect2, Scalar(0, 255, 255), 1);
	}

	cout << "||||||||||| Korulbelul ennyi walrus van a kepen: " << floor(count / 2) << endl;

	imshow("eredmeny", walrus);
	waitKey(0);

	return 0;
}