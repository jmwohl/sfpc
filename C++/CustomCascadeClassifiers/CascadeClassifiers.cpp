/**
 * @file objectDetection2.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );
int detectNumAttachedCvCameras();

/** Global variables */
String circle_cascade_name = "classifier/cascade.xml";
CascadeClassifier circle_cascade;
String window_name = "Capture - Circle detection";
/**
 * @function main
 */
int main( void ) {
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascade
    if ( !circle_cascade.load( circle_cascade_name ) ) {
        printf("--(!)Error loading circle cascade\n");
        return -1;
    };

    // cout << detectNumAttachedCvCameras() << endl;
    int camNum = detectNumAttachedCvCameras();
    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) {
        printf("--(!)Error opening video capture\n");
        return -1;
    } else {
        cout << "cam is opened" << endl;
    }

    // for (;;) {
    //     if(waitKey(30) >= 0) break;

    //     Mat frame;
    //     capture >> frame;

    //     if(frame.empty()){
    //         std::cerr<<"frame is empty"<<std::endl;
    //         continue;
    //     }

    //     imshow(window_name, frame);


    // }

    while ( capture.read(frame) ) {
        if ( frame.empty() ) {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );

        //-- bail out if escape was pressed
        int c = waitKey(10);
        if ( (char)c == 27 ) {
            break;
        }
    }
    return 0;
}

int detectNumAttachedCvCameras() {
    int number = 0;
    while (true) {
        VideoCapture cap;
        cap.open(number);
        if (!cap.isOpened()) {
            break;
        } else {
            number++;
            cap.release();
        }
    }
    return number;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame ) {
    std::vector<Rect> circles;
    Mat frame_gray, frame_thresh;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    threshold(frame_gray, frame_thresh, 200, 255, CV_THRESH_BINARY);

    //-- Detect circles
    // circle_cascade.detectMultiScale(const cv::Mat &image, vector<Rect> &objects, vector<int> &rejectLevels, vector<double> &levelWeights)
    circle_cascade.detectMultiScale( frame_thresh, circles, 1.1, 2, 0, Size(300, 300) );

    if (circles.size()) {
        //-- Draw the circle
        Point center( circles[0].x + circles[0].width / 2, circles[0].y + circles[0].height / 2 );
        // rectangle(frame, circles.front(), Scalar(255, 0, 0));
        ellipse(frame, center, Size(5, 5), 0, 0, 360, Scalar(0,0,255), 5, 8, 0);
        // circle(frame, center, Size(5,5), Scalar)
        ellipse( frame, center, Size( circles[0].width / 3, circles[0].height / 3 ), 0, 0, 360, Scalar( 0, 255, 0 ), 5, 8, 0 );
    }
    // for ( size_t i = 0; i < circles.size(); i++ ) {
    //     Mat faceROI = frame_thresh( circles[i] );

    //     //-- Draw the circle
    //     Point center( circles[i].x + circles[i].width / 2, circles[i].y + circles[i].height / 2 );
    //     ellipse( frame, center, Size( circles[i].width / 2, circles[i].height / 2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

    // }
    //-- Show what you got
    imshow( window_name, frame );
}
