#ifndef IMAGES_H
#define IMAGES_H

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

#include <opencv2/core/core.hpp>        // Mat
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <iostream>                     // std::cout
#include <string>                       // std::string

using namespace cv;

int showLenna(void) {
    // Read the file, lenna.jpg is a picture at the same location that this file and main.cpp
    Mat image = imread("Inputs\\Images\\lenna.jpg", IMREAD_COLOR);

    // Check for invalid input
    if (image.empty())
    {
        std::cout << "Could not open or find the image" << "\n";
        return -1;
    }

    // Create a window for display
    namedWindow("Display window", WINDOW_AUTOSIZE);

    // Show our image inside it
    imshow("Display window", image);

    // Wait for a keystroke in the window
    waitKey(0);

    return 0;
}

int showImg(const std::string& imgName) {
    Mat image = imread(imgName, IMREAD_COLOR);

    // Check for invalid input
    if (image.empty())
    {
        std::cout << "Could not open or find the image" << "\n";
        return -1;
    }

    // Create a window for display
    namedWindow("Original Picture " + imgName, WINDOW_AUTOSIZE);

    // Show our image inside it
    imshow("Original Picture " + imgName, image);

    // Wait for a keystroke in the window
    waitKey(0);

    return 0;
}

#endif // IMAGES_H