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

	// turn to gray image
	Mat gr(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gr, COLOR_BGR2GRAY);

	//get a copy of the gray image
	Mat output = gr.clone();

	//cretae variables for x and y direction gradients
	int gx = 0;
	int gy = 0;
	int G = 0;

	//full image loop

	//for (int i = 0; i < height - 1; i++) {
	//	for (int j = 0; j < width - 1; j++) {
	//		
	//		//kernel 
	//		gx = gr.at<uchar>(i, j) - gr.at<uchar>(i, j + 1);
	//		gy = gr.at<uchar>(i, j) - gr.at<uchar>(i + 1, j);

	//		//get overall gradient
	//		G = abs(gx) + abs(gy);

	//		//logic
	//		if (G >= 30) 
	//			output.at<uchar>(i, j) = 255;
	//		else
	//			output.at<uchar>(i, j) = 0;
	//		
	//			
	//			}
	//		}
		

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			//kernel 
			gx = -1 * gr.at<uchar>(i-1, j-1) + -2 * gr.at<uchar>(i-1, j) + -1 * gr.at<uchar>(i-1,j+1) + 1 * gr.at<uchar>(i+1,j-1) + 2 * gr.at<uchar>(i+1 ,j) + 1 * gr.at<uchar>(i+1,j+1);
			gy = -1 * gr.at<uchar>(i-1, j-1) + -2 * gr.at<uchar>(i , j-1) + -1 * gr.at<uchar>(i+1,j-1) + 1 * gr.at<uchar>(i-1,j+1) + 2 * gr.at<uchar>(i,j+1) + 1 * gr.at<uchar>(i+1,j+1);


			//get overall gradient
			G = abs(gx) + abs(gy);

			//logic
			if (G >= 100)
				output.at<uchar>(i, j) = 255;
			else
				output.at<uchar>(i, j) = 0;


		}
	}

	namedWindow("Gray");
	imshow("Gray", gr);
	namedWindow("Output");
	imshow("Output", output);

	waitKey(0);
	return 0;

}