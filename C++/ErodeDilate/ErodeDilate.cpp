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

    imshow( "Output", threshMat );
    
    while(true) {
        char k;
        k = waitKey(0);
        int kInt = (int) k;
        cout << kInt << endl;

        if (k == 0) {
            cout << "dilate!" << endl;
            dilate(threshMat);
        }

        if (kInt == 1) {
            cout << "erode!" << endl;
            erode(threshMat);
        }

        if (k == 'q') {
            return 0;
        }

        imshow("Output", threshMat);
    }

}