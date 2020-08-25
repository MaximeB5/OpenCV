#ifndef DETECTPEOPLEHOG_H
#define DETECTPEOPLEHOG_H

/* We're using the x64 version of openCV.
 * Make sure this is the correct version on Visual Studio (and not x86 as default).
 * This can be check above, between "Debug" or "Release" and "Local Windows Debugger".
 *
 * After adding "C:\opencv\build\x64\vc14\bin" to your PATH environment variable (considering you installed it directly on C:),
 * Remember to link Visual Studio to OpenCV to be able to use it.
 * Follow those instructions to do it :
 *  1. In Visual Studio, right click on your project in the Solution Explorer and click on Properties.
 *  2. Go to C/C++, then General, and select Additionnal Include Directories. That's here we need to add the path to OpenCV directory.
 *     According to the previous path you added to your PATH environment variable, this should be "C:\opencv\build\include".
 *     Paste this path in the Additionnal Include Directories and then click on Apply.
 *  3. Still in the Properties, go on Linker, then General, and select Additionnal Library Directories.
 *     Paste the path to the lib "C:\opencv\build\x64\vc14\lib" here, and click on Apply.
 *     Take care about the Configuration setting on top of this window, we're configuring it for Active(Debug), but you can do the same for Release if you want.
 *  4. Now, still in Linker, go to Input. We'll add Additionnal Dependencies. At the end of this line, click on the arrow cursor and click on Edit.
 *     The dependencies we're adding are in the "C:\opencv\build\x64\vc14\lib" folder, there are the *.lib files.
 *     It should be "opencv_world***.lib" and "opencv_world***d.lib" where *** are 3 numbers for the openCV version you have.
 *     Paste them in this window and then click on OK, then click on Apply and OK.
 *
 * Congrats, you're done with configuring and linking OpenCV to Visual Studio, you should not have any include errors now.
 * Have fun and enjoy OpenCV ! :)
 *
 * ~ Help Tutorial by Maxime Belaval, 19/08/2020 ~
 *
 * IN CASE OF EXCEPTION THROWN BY IMSHOW :
 * It appeared that, using OpenCV with Visual Studio in Debug mode instead of CMake, can let imshow throws exception.
 * A solution, if re-building doesn't work, is to set the compile in Release (still with x64) rather than Debug.
 */

#include "Images.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;

void resizeBoxes(Rect& box);

int detectPeopleUsingHistogramOfOrientedGradients(void) {
	// Load the input
	constexpr char imgName[] = "Inputs\\Images\\rue2.jpg";
	Mat img = imread(imgName);

	// Check the file is valid
	if (img.empty() or !img.data)
	{
		std::cout << "Could not open or find the image" << "\n";
		return -1;
	}

	// Histogram of Oriented Gradients
	HOGDescriptor hog;

	// People detection : getDefaultPeopleDetector will give us the coefficients of classifying trend for people detection
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	std::vector<Rect> detections;

	// Now we can begin the detection
	// arguments :		 input array image, detection based tracker::tracked object::positions vector found location,
	//					 hit threshold, win stride, padding		--> values to play with for a better detection
	//					 scale, final threshold					--> values to play with for a better detection
	//					 use mean shift grouping
	hog.detectMultiScale(img, detections,
						 0.0, Size(8, 8), Size(32, 32),
						 1.2, 2,
						 false);

	// Draw the boxes around what we've detected
	for (auto& detection : detections) {
		resizeBoxes(detection);
		rectangle(img, detection.tl(), detection.br(), Scalar(255, 0, 0), 2);
	}

	namedWindow("People Detection Results");
	imshow("People Detection Results", img);
	waitKey(0);

	//return 0;
	return showImg(imgName);
}

void resizeBoxes(Rect& box) {
	box.x += cvRound(box.width * 0.1);
	box.width = cvRound(box.width * 0.8);

	box.y += cvRound(box.height * 0.06);
	box.height = cvRound(box.height * 0.8);
}

#endif // DETECTPEOPLEHOG_H