#include "main.h"

//==================================================================================================================
//Variables
//==================================================================================================================


//Mats
Mat inImg;

//Template mats
Mat fullScreen;
Mat vertSplit;
Mat horSplit;
Mat horBottRect;
Mat horTopRect;
Mat vertRightRect;
Mat vertLeftRect;
Mat fourSplit;

//==================================================================================================================
//High-level and image processing methods
//==================================================================================================================

int main(int agrc, char ** argv) {

	inImg = readImage("split.jpg");

	IplImage  inImgIpl = inImg;
	Mat z(inImg.rows, inImg.cols, inImg.type());
	IplImage outImgIpl = z;

	//Smooth and get edges, as shown here: http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/laplace_operator/laplace_operator.html
	GaussianBlur(inImg, inImg, Size(3,3), 0, 0, BORDER_CONSTANT);
	cvLaplace(&inImgIpl, &outImgIpl);

	Mat outImg = cvarrToMat(&outImgIpl);
	showImage(outImg, "test");

	//Create image templates
	makeTemplates(outImg.rows, outImg.cols, outImg.type());

	return 0;
}

void makeTemplates(int rows, int columns, int imgType) {

	
}

//==================================================================================================================
//Helper methods
//==================================================================================================================

Mat readImage(const char * fileName) {

	Mat image = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);

	if (image.empty()) {

		printf("%s wasn't found!  Please ensure the file exists and that you've specified the correct path\n", fileName);
		system("pause"); //wait for a key press
		exit(1);
	}

	//read the images in specified by the command arguments
	return image;
}

void showImage(Mat image, char * windowTitle) {

	namedWindow(windowTitle, CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow(windowTitle, image); //display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(0); //wait infinite time for a keypress

	destroyWindow(windowTitle); //destroy the window with the name, "MyWindow"
}