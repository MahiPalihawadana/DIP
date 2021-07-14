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

	int G = 0;

	//Laplacian Operator
	for (int i = 2; i < height - 2; i++) {
		for (int j = 2; j < width - 2; j++) {
		
		//G = -gr.at<uchar>(i + 1, j) - gr.at<uchar>(i - 1, j) - gr.at<uchar>(i, j + 1) - gr.at<uchar>(i, j - 1) + 4 * (gr.at<uchar>(i, j));
		G = -gr.at<uchar>(i -1, j -1) - gr.at<uchar>(i, j -1) - gr.at<uchar>(i +1, j -1) - gr.at<uchar>(i -1, j) - gr.at<uchar>(i + 1, j) - gr.at<uchar>(i - 1, j +1) - gr.at<uchar>(i, j +1) - gr.at<uchar>(i + 1, j +1) + 8 * (gr.at<uchar>(i, j));

			if (G < 0) {
				//G = 0;
				output.at<uchar>(i, j) = 0;
			}
			else if(G > 255 ){
				//G = 255;
				output.at<uchar>(i, j) = 255;
			}
			else {
				output.at<uchar>(i, j) = G;
			}
				
		}
	}

	namedWindow("Gray");
	imshow("Gray", gr);
	namedWindow("Output");
	imshow("Output", output);

	imwrite("New Image.jpg", output);
	

	waitKey(0);
	return 0;

}