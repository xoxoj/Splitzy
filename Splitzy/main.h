#pragma once

#include <iostream>
#include <map>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat readImage(const char * fileName);
void showImage(Mat image, char * windowTitle);

void extractSubScreens(Mat *);
void calculateNorm(Mat *);
void createComposite(Mat& inImage);
void makeTemplates(int rows, int columns, int imgType);