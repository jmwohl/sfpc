#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * Return an array of 8-connected neighbor values
 *
 * |3|2|1|
 * |4|*|0|
 * |5|6|7|
 *
 * @param  img [description]
 * @return     [description]
 */
vector<int> getNeighbors(const Mat &img, int j, int i, int type = 0) {
	Size size = img.size();
    int w = size.width;
    int h = size.height;

    int i_m_1 = i - 1;
    int i_p_1 = i + 1;

    if (i_m_1 < 0) i_m_1 = 0;
    if (i_p_1 > w - 1) i_p_1 = w - 1;

    int j_m_1 = j - 1;
    int j_p_1 = j + 1;

    if (j_m_1 < 0) j_m_1 = 0;
    if (j_p_1 > h - 1) j_p_1 = h - 1;

    int neighbors[8] = {
        img.at<uchar>(i_p_1, j),        // e
        img.at<uchar>(i_p_1, j_m_1),    // ne
        img.at<uchar>(i, j_m_1),        // n
        img.at<uchar>(i_m_1, j_m_1),    // nw
        img.at<uchar>(i_m_1, j),        // w
        img.at<uchar>(i_m_1, j_p_1),    // sw
        img.at<uchar>(i, j_p_1),        // s
        img.at<uchar>(i_p_1, j_p_1)     // se
    };

    std::vector<int> nV;
    nV.assign(neighbors, neighbors + 8);

    return nV;
}

/**
 * Erodes from a src image to the dst image.
 * @param src [description]
 * @param dst [description]
 */
void erode(Mat &src, Mat &dst) {
    // Mat tmp = src.clone();

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pDst = dst.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            std::vector<int> naybrs = getNeighbors(src, col, row);
            for (int b = 0; b < naybrs.size(); ++b) {
                if (naybrs.at(b) == 0) {
                    *pDst = 0;
                    break;
                }
            }
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pDst++;
        }
    }
}

/**
 * Erode an image directly.
 * @param src [description]
 */
void erode(Mat &src) {
    Mat tmp = src.clone();

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pDst = tmp.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            std::vector<int> naybrs = getNeighbors(src, col, row);
            for (int b = 0; b < naybrs.size(); ++b) {
                if (naybrs.at(b) == 0) {
                    *pDst = 0;
                    break;
                }
            }
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pDst++;
        }
    }
    tmp.copyTo(src);
}

/**
 * Dilate an image.
 * @param src [description]
 */
void dilate(Mat &src) {
    Mat tmp = src.clone();

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pDst = tmp.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            std::vector<int> naybrs = getNeighbors(src, col, row);
            for (int b = 0; b < naybrs.size(); ++b) {
                if (naybrs.at(b) == 255) {
                    *pDst = 255;
                    break;
                }
            }
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pDst++;
        }
    }
    tmp.copyTo(src);
}