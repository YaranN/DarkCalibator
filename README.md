# DarkCalibator
1. The application was developed by using Visual Studio under Windows 10 platform. 
2. In order to run the program, please download the zip file and unzip.
3. Open the cmd promt and make sure it directs to the DarkCalibrator/
4. Uisng follow cmd format to start the program. 
   Exmaple :"DarkCalibrator.exe DSC.jpg TestImage_A.jpg 80 80"
Thought about TestImage_B:
1. The reason of why it is not working is due to the locations of white areas on DSC and TestImage_B are different. 
   Therefore, the adjustment mask cannot be used directly on the the testImage_B
   
2. The next step is either mapping those location with adjustment mask or apply adjustment mask in a dynamical way.
