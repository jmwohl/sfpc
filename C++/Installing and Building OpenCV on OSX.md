# Installing and Building OpenCV of OSX

### Setting up SublimeText for C/C++ development

If you haven't already, you'll want to set up SublimeText for C/C++ development.  [see link]

### Installing OpenCV on OSX 10.8

Following several examples online, I attempted to build openCV from source, using cmake and make.  This failed for me.  In the end, I was able to successfully install the library using homebrew... this too wasn't as straightforward as I'd hoped, since I needed to add the homebrew/science repos before opencv showed up as a package:

```bash
$ brew tap homebrew/science
$ brew install opencv
```

That did the trick, installing the necessary dependencies, building opencv, and sticking the dynamic libraries in /usr/local/bin.

Next I needed to figure out how to include the libraries when building a c++ application.  I copied a small example from the OpenCV site, and called it DisplayImage.cpp:

```c++
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char **argv ) {
    Mat image;
    image = imread( argv[1], 0 );

    if ( argc != 2 || !image.data ) {
        printf( "No image data \n" );
        return -1;
    }

    namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    imshow( "Display Image", image );

    waitKey(0);

    return 0;
}
```

And attempted to build using g++:

```bash
$ g++ -o DisplayImage DisplayImage.cpp
```

Of course, this failed because the compiler couldn't find the OpenCV libs.  So I read a little about linking, and after some trial and error found that I could link to the necessary libs using g++'s -l flag:

```bash
$ g++ -o DisplayImage DisplayImage.cpp -lopencv_core -lopencv_highgui
```

And VIOLA!  I ended up with a little application that opened an image.  Yay!