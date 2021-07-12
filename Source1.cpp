#include "cv.h"
#include "highgui.h"

int main(int argc, char* argv[]) {
	IplImage* img;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!img){
		printf("Could not load image file: %s\n", argv[1]);
	return -1;
}

	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvReleaseImage(&img);
	return 0;
}