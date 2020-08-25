#ifndef VIDEOS_H
#define VIDEOS_H

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
#include <opencv2/videoio.hpp>          // VideoCapture, VideoWriter
#include <opencv2/highgui/highgui.hpp>  // Gui
#include <iostream>                     // std::cout

using namespace cv;

int showMyWebcam(void) {
    // Capture video using the default video source (i.e. webcam)
    VideoCapture video(0);

    // Check that video opened
    if (!video.isOpened()) return -1;

    // For saving the frames from the video
    Mat frame;

    // Get the video resolution
    int frameWidth = video.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(CAP_PROP_FRAME_HEIGHT);

    // Video writer object - params : name, encodec, fps, video resolution
    // FPS : 60 might be a bit fast as a result in the video output, 30 is decent (but sometimes faster than the real stream)
    VideoWriter output("Outputs\\Videos\\out_Webcam.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    while (video.read(frame)) {
        // Display the frame
        imshow("Video output", frame);

        // Write video frame
        output.write(frame);

        // To end the video early
        if (waitKey(25) >= 0) break;
    }

    // Release video capture and writer
    output.release();
    video.release();

    destroyAllWindows();

    return 0;
}


int showWinrunner(void) {
    // Capture video using a video at the same location that this file and main.cpp
    VideoCapture video("Inputs\\Videos\\Winrunner.mp4");

    // Check that video opened
    if (!video.isOpened()) return -1;

    // For saving the frames from the video
    Mat frame;

    // Get the video resolution
    int frameWidth = video.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(CAP_PROP_FRAME_HEIGHT);

    // Video writer object - params : name, encodec, fps, video resolution
    // FPS : 60 might be a bit fast as a result in the video output, 30 is decent (but sometimes faster than the real stream)
    VideoWriter output("Outputs\\Videos\\out_Winrunner.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    while (video.read(frame)) {
        // Display the frame
        imshow("Video output", frame);

        // Write video frame
        output.write(frame);

        // To end the video early
        if (waitKey(25) >= 0) break;
    }

    // Release video capture and writer
    output.release();
    video.release();

    destroyAllWindows();

    return 0;
}

#endif // VIDEOS_H
