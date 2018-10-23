#pragma once

void readImage(std::string imageFile, Mat& image);
/***********************************************************************************************
*  @Purpose: Helper function to load image data
*
*  @Input: string imageFile file loacation
*          Mat& Image Refernce of the DSC.jpg pixel data
*              
*
*  @Ouptut: None
*/

void readImage(std::string imageFile, Mat& Image)
{
	Image = imread(imageFile);
	if (!Image.data) {
		std::cerr << "Error loading" << imageFile << std::endl;
	}
}