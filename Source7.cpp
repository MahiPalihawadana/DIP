#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp" 
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"


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
	int  widthstep = img.step;
	int ch = img.channels();

	Mat gr(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gr, COLOR_BGR2GRAY);


	Mat output = gr.clone();

	int G = 0;
	//int L3 = 0;

	int T = atoi(argv[2]);

	for (int x = 2; x < height - 2; x++) {
		for (int y = 2; y < width - 2; y++) {

			//G = gr.at<uchar>(i + 1, j) + gr.at<uchar>(i - 1, j) + gr.at<uchar>(i, j + 1) + gr.at<uchar>(i, j - 1) - 4 * (gr.at<uchar>(i, j));
			G = 2 * gr.at<uchar>(x, y + 1) +
				2 * gr.at<uchar>(x, y - 1) +
				2 * gr.at<uchar>(x + 1, y) +
				2 * gr.at<uchar>(x - 1, y) +
				gr.at<uchar>(x, y + 2) +
				gr.at<uchar>(x, y - 2) +
				gr.at<uchar>(x + 2, y) +
				gr.at<uchar>(x - 2, y) +
				gr.at<uchar>(x - 1, y + 1) +
				gr.at<uchar>(x + 1, y + 1) +
				gr.at<uchar>(x + 1, y - 1) +
				gr.at<uchar>(x - 1, y - 1) -
				16 * gr.at<uchar>(x, y);

			/*if (G < 0) {
				G = 0;
			}
			else if (G > 255) {
				G = 255;
			}

			output.at<uchar>(i, j) = G;
			G = 0;*/

			if (G < 0) {
				output.at<uchar>(x, y) = 0;
			}
			else if (G > 255) {
				output.at<uchar>(x, y) = 255;
			}
			else {
				//output.at<uchar>(y, x) = (G - 1020) * 255 / 2040;
				output.at<uchar>(x, y) = G;
			}

		}
	}


	namedWindow("Image");
	imshow("Image", img);
	namedWindow("Output Image");
	imshow("Output Image", output);
	imwrite("file1.jpg", output);
	waitKey(0);
	return 0;

}