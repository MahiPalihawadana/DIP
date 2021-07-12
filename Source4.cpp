#include "opencv2/opencv.hpp"
#include "opencv2//highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;

	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();


	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

	int sum;
	int avg = 0;

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			sum = 0;
			for (int g = i - 1; g <= i + 1; g++) {
				for (int h = j - 1; h <= j + 1; h++) {
					sum = sum + (int)gray.at<uchar>(g, h);
				}
			}
			avg = sum / 9;
			output.at<uchar>(i, j) = (uchar)avg;
		}
	}

	


	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Output");
	imshow("Output", output);

	waitKey(0);
	return 0;





}