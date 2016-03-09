#include "main.h"

//==================================================================================================================
//Variables
//==================================================================================================================


//Mats
Mat sourceImg;
Mat outImg;
Mat * bestFit = nullptr;
unsigned long bestFitNorm = 0;

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

	sourceImg = readImage("split2.jpg", true);
	Mat sourceImgCol = readImage("split2.jpg", false);

	//set to maximum value
	bestFitNorm -= 1;

	//Smooth and get edges, as shown here: http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/laplace_operator/laplace_operator.html
	GaussianBlur(sourceImg, outImg, Size(3,3), 0, 0, BORDER_CONSTANT);
	Laplacian(outImg, outImg, CV_8UC1, 3);
	increaseContrast(outImg);

	//Create image templates
	makeTemplates(outImg.rows, outImg.cols, outImg.type());

	//show images
	showImage(sourceImgCol, "InputImage");
	showImage(outImg, "Output Image (Laplacian)");

	/*showImage(vertSplit, "Template");
	showImage(horSplit, "Template");
	showImage(horBottRect, "Template");
	showImage(horTopRect, "Template");
	showImage(vertRightRect, "Template");
	showImage(vertLeftRect, "Template");
	showImage(fourSplit, "Template");*/

	//create each composite image
	createComposite(vertSplit);
	createComposite(horSplit);
	createComposite(horBottRect);
	createComposite(horTopRect);
	createComposite(vertRightRect);
	createComposite(vertLeftRect);
	createComposite(fourSplit);

	//calculate the norm
	cout << "vert split norm: "; calculateNorm(&vertSplit);
	cout << "hor split norm: "; calculateNorm(&horSplit);
	cout << "horBottRect norm "; calculateNorm(&horBottRect);
	cout << "horTopRect norm: "; calculateNorm(&horTopRect);
	cout << "verRight norm: "; calculateNorm(&vertRightRect);
	cout << "vertLeft norm: "; calculateNorm(&vertLeftRect);
	cout << "fourSplit norm: "; calculateNorm(&fourSplit);

	//extract and show the subscreens
	showImage(*bestFit, "the best fit!");
	extractSubScreens(&sourceImgCol);

	return 0;
}

void extractSubScreens(Mat * inImg) {

	if (bestFit == &fourSplit) {
		Mat tSubScreen;
		Mat tl, tr, bl, br;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols/2, inImg->rows/2));
		tSubScreen.copyTo(tl);

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, 0, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(tr);

		tSubScreen = Mat(*inImg, Rect(0, inImg->rows / 2, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(bl);

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, inImg->rows / 2, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(br);

		showImage(tl, "Top Left");
		showImage(tr, "Top Right");
		showImage(bl, "Bottom Left");
		showImage(br, "Bottom Right");
	
	}
	else if (bestFit == &horSplit) {

		Mat tSubScreen;
		Mat t, b;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(t);

		tSubScreen = Mat(*inImg, Rect(0, inImg->rows / 2, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(b);

		showImage(t, "Top Left");
		showImage(b, "Top Right");

	}
	else if (bestFit == &horBottRect) {
		
		Mat tSubScreen;
		Mat tl, tr, b;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(tl);

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, 0, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(tr);

		tSubScreen = Mat(*inImg, Rect(0, inImg->rows / 2, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(b);

		showImage(tl, "Top Left");
		showImage(tr, "Top 'right");
		showImage(b, "Bottom");

	}
	else if (bestFit == &horTopRect) {

		Mat tSubScreen;
		Mat t, bl, br;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(t);

		tSubScreen = Mat(*inImg, Rect(0, inImg->rows / 2, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(bl);

		tSubScreen = Mat(*inImg, Rect((inImg->cols / 2), inImg->rows / 2, inImg->cols/2, inImg->rows / 2));
		tSubScreen.copyTo(br);

		showImage(t, "Top");
		showImage(bl, "Bottom Left");
		showImage(br, "Bottom Right");

	}
	else if (bestFit == &vertLeftRect) {
		Mat tSubScreen;
		Mat l, rt, rb;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols / 2, inImg->rows));
		tSubScreen.copyTo(l);

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, 0, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(rt);

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, inImg->rows / 2, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(rb);

		showImage(l, "Left");
		showImage(rt, "Right Top");
		showImage(rb, "Right Bottom");
	}
	else if (bestFit == &vertLeftRect) {
		Mat tSubScreen;
		Mat l, lt, lb;

		tSubScreen = Mat(*inImg, Rect(inImg->cols / 2, 0, inImg->cols / 2, inImg->rows));
		tSubScreen.copyTo(l);

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols / 2, inImg->rows / 2));
		tSubScreen.copyTo(lt);

		tSubScreen = Mat(*inImg, Rect(0, inImg->rows / 2, inImg->cols, inImg->rows / 2));
		tSubScreen.copyTo(lb);

		showImage(l, "Left");
		showImage(lt, "Right Top");
		showImage(lb, "Right Bottom");
	}
	else if (bestFit == &vertSplit) {

		Mat tSubScreen;
		Mat l, r;

		tSubScreen = Mat(*inImg, Rect(0, 0, inImg->cols/2, inImg->rows));
		tSubScreen.copyTo(l);

		tSubScreen = Mat(*inImg, Rect(inImg->cols/2, 0, inImg->cols/2, inImg->rows));
		tSubScreen.copyTo(r);

		showImage(l, "Top Left");
		showImage(r, "Top Right");

	}
}

void calculateNorm(Mat * inImage) {

	//calculate the norm
	unsigned long unsquaredNorm = 0;

	for (int r = 0; r < sourceImg.rows; ++r) {
		for (int c = 0; c < sourceImg.cols; ++c) {

			unsquaredNorm += (*inImage).at<uchar>(r, c)*(*inImage).at<uchar>(r, c);

		}
	}

	unsigned long norm = sqrt(unsquaredNorm);
	
	cout << norm << ". Unsquared norm: " << unsquaredNorm << endl;

	//if this norm is lower, store it
	if (norm < bestFitNorm) {
		cout << "found a better norm"<< endl;
		bestFitNorm = norm;
		bestFit = inImage;
	}

}

void createComposite(Mat& inImage){

	for (int r = 0; r < sourceImg.rows; ++r) {
		for (int c = 0; c < sourceImg.cols; ++c) {

			inImage.at<uchar>(r, c) = abs(inImage.at<uchar>(r, c) - outImg.at<uchar>(r, c));

		}
	}
}

void increaseContrast(Mat & inImage){

	for (int r = 0; r < sourceImg.rows; ++r) {
		for (int c = 0; c < sourceImg.cols; ++c) {

			if (inImage.at<uchar>(r, c) > 40) {
				
				inImage.at<uchar>(r, c) = 255;
			}
		}
	}
}

void makeTemplates(int rows, int columns, int imgType) {

	Scalar backgroundColor = Scalar(0, 0, 0);
	Scalar lineColor = Scalar(255, 255, 255);
	int lineWidth = 1;

	vertSplit = Mat(rows, columns, imgType);
	vertSplit.setTo(backgroundColor);
	line(vertSplit, Point(columns/2, 0), Point(columns/2, rows), lineColor, lineWidth);

	horSplit = Mat(rows, columns, imgType);
	horSplit.setTo(backgroundColor);
	line(horSplit, Point(0, rows/2), Point(columns, rows/2), lineColor, lineWidth);

	horBottRect = Mat(rows, columns, imgType);
	horBottRect.setTo(backgroundColor);
	line(horBottRect, Point(columns / 2, 0), Point(columns / 2, rows/2), lineColor, lineWidth); //vertical line
	line(horBottRect, Point(0, rows / 2), Point(columns, rows / 2), lineColor, lineWidth); //horizontal line

	horTopRect = Mat(rows, columns, imgType);
	horTopRect.setTo(backgroundColor);
	line(horTopRect, Point(columns / 2, rows), Point(columns / 2, rows / 2), lineColor, lineWidth); //vertical line
	line(horTopRect, Point(0, rows / 2), Point(columns, rows / 2), lineColor, lineWidth); //horizontal line

	vertRightRect = Mat(rows, columns, imgType);
	vertRightRect.setTo(backgroundColor);
	line(vertRightRect, Point(columns / 2, 0), Point(columns / 2, rows), lineColor, lineWidth); //vertical line
	line(vertRightRect, Point(0, rows / 2), Point(columns / 2, rows / 2), lineColor, lineWidth); //horizontal line

	vertLeftRect = Mat(rows, columns, imgType);
	vertLeftRect.setTo(backgroundColor);
	line(vertLeftRect, Point(columns / 2, 0), Point(columns / 2, rows), lineColor, lineWidth); //vertical line
	line(vertLeftRect, Point(columns / 2, rows / 2), Point(columns, rows / 2), lineColor, lineWidth); //horizontal line

	fourSplit = Mat(rows, columns, imgType);
	fourSplit.setTo(backgroundColor);
	line(fourSplit, Point(columns / 2, 0), Point(columns / 2, rows), lineColor, lineWidth); //vertical line
	line(fourSplit, Point(0, rows / 2), Point(columns, rows / 2), lineColor, lineWidth); //horizontal line
}

//==================================================================================================================
//Helper methods
//==================================================================================================================

Mat readImage(const char * fileName, bool greyScale) {

	Mat image = (greyScale) ? imread(fileName, CV_LOAD_IMAGE_GRAYSCALE) : imread(fileName);

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
	
	try {
		imshow(windowTitle, image); //display the image which is stored in the 'img' in the "MyWindow" window
		waitKey(0); //wait infinite time for a keypress
		
	} catch(cv::Exception) {
		cout << "Error occured whilst trying to open " << windowTitle << endl;
		waitKey(0); //wait infinite time for a keypress
	}
	
	destroyWindow(windowTitle); //destroy the window with the name, "MyWindow"
}