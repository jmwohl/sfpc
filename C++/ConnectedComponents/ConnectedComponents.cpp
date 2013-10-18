#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ProcessImage.cpp"

using namespace std;
using namespace cv;

/// Global variables

int threshold_value = 128;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, threshMat, erodedMat, dilatedMat;
Size size;

/**
 * @function main
 */
int main( int argc, char **argv ) {
    // Load an image
    src = imread( argv[1], 1 );
    size = src.size();

    // Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    // Create a window to display results
    namedWindow( "Output", CV_WINDOW_AUTOSIZE );

    // Create a thresholded image
    threshold( src_gray, threshMat, threshold_value, max_BINARY_value, threshold_type );

    Mat contoursMat = Mat(size, CV_8UC1);

    imshow( "Output", threshMat );
    
    while(true) {
        char k;
        k = waitKey(0);
        int kInt = (int) k;
        cout << kInt << endl;

        if (k == 'c') {
            cout << "connected components!" << endl;
            connectedRegions(threshMat);
        }

        if (k == 'o') {
            cout << "contours!" << endl;
            findContours(threshMat, contoursMat);
            imshow("Output", contoursMat);
        }

        if (k == 'n') {
            vector<int> test = getNeighbors(threshMat, 3, 3, 1);
            printVector(test);
        }

        if (k == 0) {
            cout << "dilate!" << endl;
            dilate(threshMat);
            imshow("Output", threshMat);
        }

        if (kInt == 1) {
            cout << "erode!" << endl;
            erode(threshMat);
            imshow("Output", threshMat);
        }

        if (k == 'b') {
            cout << "gaussianBlur!" << endl;
            gaussianBlur(threshMat);
            imshow("Output", threshMat);
        }

        if (k == 'q') {
            return 0;
        }
    }

}