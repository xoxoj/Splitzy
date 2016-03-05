#pragma once

#include <iostream>
#include <map>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat readImage(const char * fileName);
void showImage(Mat image, char * windowTitle);
void makeTemplates(int rows, int columns, int imgType);