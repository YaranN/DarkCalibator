#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;
enum InputType { 
	NO_IMAGE = 1, 
	ONE_IMAGE = 2, 
	TWO_IMAGE_DEFAULT_AUTO= 3, 
	TWO_IMAGE_AUTO=4
};
enum CALI_MODE { 
	MAN_CALIBRATE = 0, 
	AUTO_CALIBRATE = 1
};

class Adjustment {
 public:
	 void createAdjustmentMask(Mat& DSCImage, Mat& AdjustmentMask,int& x, int& y, int mode);
	 void calibrateImage(Mat& ImageToCalibrate, Mat& AdjustmentMask);

};
/***********************************************************************************************
*  @Purpose: Create adjustmask mask for later calibration use
*
*  @Input: Mat& DSCImage Refernce of the DSC.jpg pixel data
*          Mat& AdjustmentMask Reference of the AdjustmentMask
*          int& x, y position of the defined true black target
*          int mode Calibration mode (auto OR manual
*
*  @Ouptut: None
*/

void Adjustment::createAdjustmentMask(Mat& DSCImage, Mat& AdjustmentMask, int& x, int& y, int mode) {
	Mat TrueBlack, Grey;
	// Set it to defualt color black
	double cal_black_color = 0;
	cvtColor(DSCImage, Grey, COLOR_BGR2GRAY);
	if (mode == AUTO_CALIBRATE)
	{
		minMaxLoc(Grey, &cal_black_color,NULL, NULL);
	}
	else
	{
		cal_black_color = Grey.at<uint8_t>(x, y);

	}
	std::cout <<"True black value:" << cal_black_color << std::endl;
	Mat Trueblack(DSCImage.rows, DSCImage.cols, CV_8UC1, Scalar::all(cal_black_color));
	AdjustmentMask = Grey - TrueBlack;


}
/***********************************************************************************************
*  @Purpose: Calibrate the test image 
*
*  @Input: Mat& ImageToCalibrate Refernce of the testImage pixel data
*          Mat& AdjustmentMask Reference of the AdjustmentMask
*
*  @Ouptut: None
*/
void Adjustment::calibrateImage(Mat& ImageToCalibrate, Mat& AdjustmentMask)
{
	Mat GreyColor;
	// Convert the image need to be calibrated to grey image
	cvtColor(ImageToCalibrate, GreyColor, COLOR_BGR2GRAY);
	// Processing the calibration
	Mat CalibratedImage = GreyColor - AdjustmentMask;
	// Finish the calibrarion and write to CalibratedImage.jpg file
	imwrite("CalibratedImage.jpg", CalibratedImage);
}