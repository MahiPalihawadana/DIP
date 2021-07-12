#include "opencv2/opencv.hpp"
#include "opencv2//highgui.hpp"
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
	int widthstep = img.step;
	int ch = img.channels();


	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

    int laplace_mask[9] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
    int tmp = 0;
    int counter = 0;
	Mat laplaceImage = cv::Mat::ones(img.rows - 2, img.cols - 2, CV_32F);

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			
			for (int g = i - 1; g <= i + 1; g++) {
				for (int h = j - 1; h <= j + 1; h++) {

					tmp += laplace_mask[counter] * static_cast<int>(img.at<uchar>(g, h));
					counter++;
				}
			}
			    std::cout << tmp << std::endl;
            laplaceImage.at<float>(i - 1, j - 1) = tmp;
            tmp = 0;
			counter = 0;
		

		}
	}


	


	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("laplaceImage");
	imshow("laplaceImage", laplaceImage);

	waitKey(0);
	return 0;





}

//using namespace cv;
//int main(int argc, char** argv)
//{
//    // Declare the variables we are going to use
//    Mat src, src_gray, dst;
//    int kernel_size = 3;
//    int scale = 1;
//    int delta = 0;
//    int ddepth = CV_16S;
//    const char* window_name = "Laplace Demo";
//
//
//    const char* imageName = argc >= 2 ? argv[1] : "ima.jpg";
//    src = imread(samples::findFile(imageName), IMREAD_COLOR); // Load an image
//    // Check if image is loaded fine
//    if (src.empty()) {
//        printf(" Error opening image\n");
//        printf(" Program Arguments: [image_name -- default lena.jpg] \n");
//        return -1;
//    }
//
//
//    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
//    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
//    cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to grayscale
//
//
//    Mat abs_dst;
//
//    Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
//    // converting back to CV_8U
//    convertScaleAbs(dst, abs_dst);
//    imshow(window_name, abs_dst);
//    waitKey(0);
//    return 0;
//}


