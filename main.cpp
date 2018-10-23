
/* 
Up to 4 Inputs.
[0] absolute path of dsc file
[1] absolute path of test image
//BELOW Inputs are optional in pair
[2] Any integer gte 0 for x coord of darkest black
[3] Any integer gte 0 for x coord of darkest black
TO USE:
Place DSC.jpg and and TestImage_A.jpg in same folder as the executable.
Program will automatically begin processing calibratedImage.jpg
Below are examples of the commands arguments
DSC.jpg TestImage_A.jpg 
DSC.jpg TestImage_A.jpg 15 15
*/
#include <iostream>
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include "adjustMask.hpp"
#include "imageHelper.hpp"

int main(int argc, char** argv)
{
	//Make it to default values
	int x_coord = 0;  //selected row of data
	int y_coord = 0;  //selected column of data
	int cal_mode = 0; //Mode of calibration
	Mat DarkImage;    // DSC image
	Mat ImageToCalibrate;  //Image need to be calibrated
	// Adjustment Image
	Mat adj_mask;     
	Adjustment Image; 

	//Dtermine the input types
	switch (argc)
	{
		// No enough input files
		case NO_IMAGE:
			std::cout <<"Please select DSC and test image file locations" << std::endl;
			return -1;
		case ONE_IMAGE:
			std::cout << "Please select test image file locations" << std::endl;
			return -1;
        // No user inputs for image calibration values
		case TWO_IMAGE_DEFAULT_AUTO:
		case TWO_IMAGE_AUTO:
			std::cout << "Auto select the coordinates!" << std::endl;
			cal_mode = AUTO_CALIBRATE;
			x_coord, y_coord = 0;
			break;
		// Use user defined values to calibrate
		default:
			cal_mode = MAN_CALIBRATE;
			x_coord = atoi(argv[3]);
			y_coord = atoi(argv[4]);
			if (x_coord < 0 || y_coord < 0)
			{
				std::cout << "x or y are not valid position. Change it to Auto calibration!" << std::endl;
				cal_mode = AUTO_CALIBRATE;
				x_coord = 0;
				x_coord = 0;
			}

	}
	// Load DSC image file
	readImage(argv[1], DarkImage);
	// Load test image to be ready for calibrating 
	readImage(argv[2], ImageToCalibrate);
	// Adjust the DSC image with true black target
	Image.createAdjustmentMask(DarkImage, adj_mask, x_coord, y_coord, cal_mode);
	// Calibration the image user want to calibrate
	Image.calibrateImage(ImageToCalibrate, adj_mask);

	return 0;
}