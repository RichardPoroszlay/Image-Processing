/*
	Becs�lje meg a napoz� rozm�rok sz�m�t az agyarak sz�ma alapj�n.

	1. Olvassa be a walrus_jeff_foot.png k�pet.
	2. K�sz�b�lje a k�k csatorna alapj�n (ne sajn�lja az id�t a megfelel� k�sz�b�rt�k megkeres�s�re)
	3. A k�ls� k�rvonalakat gy�jtse �ssze a k�sz�b�lt k�pen.
	4. Minden k�rvonalra:
		- hat�rozza meg a minim�lis befoglal� t�glalapot az al�bbi f�ggv�ny seg�ts�g�vel:
			cv::RotatedRect minAreaRect(cv::InputArray points);
		- ha a kapott t�glalap hosszabbik oldala legal�bb k�tszer olyan hossz�, mint a r�videbb oldal, akkor az adott kont�rt tekintse rozm�ragyarnak, n�veljen egy sz�ml�l�t �s rajzolja ki z�lddel a kont�rt.  
			Egy�bk�nt rajzolja ki k�kkel a kont�rt az eredeti k�pre. 
			Megj.: Sz�ks�g eset�n (pl.: ha a k�sz�b�l�se nem az igazi) a kont�r ter�lete/ker�lete alapj�n is kidobhat kont�rokat enn�l a l�p�sn�l. 

	5. �rja ki a rozm�rok becs�lt sz�m�t (norm�l esetben egy rozm�r 2 agyarral b�r). 
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