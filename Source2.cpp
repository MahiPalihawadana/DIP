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

	printf("Height: %d, Width: %d, width Step: %d,Channels: %d\n", height, width, widthstep, ch);

	img.at<uchar>(10, 10) - 255;

	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat copy(height, width, CV_8UC3, Scalar(0, 0, 0));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			copy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}


	// Histogram code begins

	//allocate memory for all the intencity values
	int hist[256];

	//Initialize "o" to all the array elements
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;

	}

	//COunt one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)] +1 ;
			
		
		}
		
	}

	for (int i = 0; i < 256; i++) {
		cout << i << ":" << hist[i] << endl;
	}
	
	//create an image to displya histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));

	//FInd Maximum number of histogram array
	int max = hist[0];
	for (int i = 0; i < 256; i++) {
		if (max < hist[i]) {
			max = hist[i];
		}
	}
	// Normalize the histogram
	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max)* histImage.rows;

	}

	//Draw the lines of the histogram
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist[i]), Scalar(0), 1, 8, 0);


	}

	// Histogram code ends

	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Copy");
	imshow("Copy", copy);
	namedWindow("Histogram");
	imshow("Histogram", histImage);

	waitKey(0);
	return 0;





}