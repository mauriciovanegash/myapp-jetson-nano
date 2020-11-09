#include <stdio.h>
#include <opencv2/opencv.hpp>
// #include <opencv2/imgproc.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main()
{
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "OpenCV camera capture:\n    Using pipeline: \n\t" << pipeline << endl;

    int ret = 0;
    Mat frame;
    VideoCapture cap(pipeline, CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera.\n";
        return -1;
    }

    cout << "Start grabbing" << endl << "Press any key to terminate" << endl;

    for (;;)
    {
        cap.read(frame);
        if (frame.empty())
        {
            cerr << "ERROR! Blank frame grabbed.\n";
            ret = -1;
            break;
        }
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return ret;
}