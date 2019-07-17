#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

	Mat lena = imread("../data/lena.png");

	namedWindow("win");
	imshow("win", lena);
	 
	cout << "Lena!" << endl;
	cvWaitKey();
	
	return 0;
}
