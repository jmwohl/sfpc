#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

// UTILITY FUNCTIONS
int randomInt(int max);
int randomInt(int min, int max);

// IMAGE PROCESSING FUNCTIONS
vector<int> getNeighbors(const Mat &img, int j, int i, int type);
void setNeighbors(Mat &img, int j, int i, uchar val);
void erode(Mat &src, Mat &dst);
void erode(Mat &src);
void dilate(Mat &src);
void gaussianBlur(Mat &src);
void connectedRegions(Mat &src, int matchValue);



int randomInt(int max) {
    srand (time(NULL));
    return (rand() % max + 1);
}

int randomInt(int min, int max) {
    srand (time(NULL));
    return min + (rand() % (max + 1) - min);
}


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
vector<int> getNeighbors(const Mat &img, int i, int j, int type = 0) {
    Size size = img.size();
    int w = size.width;
    int h = size.height;
    std::vector<int> nV;

    int i_m_1 = i - 1;
    int i_p_1 = i + 1;

    if (i_m_1 < 0) i_m_1 = 0;
    if (i_p_1 > w - 1) i_p_1 = w - 1;

    int j_m_1 = j - 1;
    int j_p_1 = j + 1;

    if (j_m_1 < 0) j_m_1 = 0;
    if (j_p_1 > h - 1) j_p_1 = h - 1;


    if (type == 0) {
        int neighbors[8] = {
            img.at<uchar>(j, i_p_1),        // e
            img.at<uchar>(j_m_1, i_p_1),    // ne
            img.at<uchar>(j_m_1, i_p_1),        // n
            img.at<uchar>(j_m_1, i_m_1),    // nw
            img.at<uchar>(j, i_m_1),        // w
            img.at<uchar>(j_p_1, i_m_1),    // sw
            img.at<uchar>(j_p_1, i),        // s
            img.at<uchar>(j_p_1, i_p_1)     // se
        };
        nV.assign(neighbors, neighbors + 8);
    }

    if (type == 1) {
        // int neighbors[4] = {
        //     img.at<uchar>(i_p_1, j_m_1),    // ne
        //     img.at<uchar>(i, j_m_1),        // n
        //     img.at<uchar>(i_m_1, j_m_1),    // nw
        //     img.at<uchar>(i_m_1, j)         // w
        // };
        // cout << "i_p_1: " << i_p_1 << endl;
        // cout << "j_m_1: " << j_m_1 << endl;

        // cout << "val: " << (int)img.at<uchar>(j_m_1, i_p_1) << endl;
        // cout << "val: " << (int)img.at<uchar>(j_m_1, i) << endl;
        // cout << "val: " << (int)img.at<uchar>(j_m_1, i_m_1) << endl;
        // cout << "val: " << (int)img.at<uchar>(j, i_m_1) << endl;

        if (img.at<uchar>(j_m_1, i_p_1) != 0) {
            // cout << "1" << endl;
            nV.push_back(img.at<uchar>(j_m_1, i_p_1));
        }
        if (img.at<uchar>(j_m_1, i) != 0) {
            // cout << "2" << endl;
            nV.push_back(img.at<uchar>(j_m_1, i));
        }
        if (img.at<uchar>(j_m_1, i_m_1) != 0) {
            // cout << "3" << endl;
            nV.push_back(img.at<uchar>(j_m_1, i_m_1));
        }
        if (img.at<uchar>(j, i_m_1) != 0) {
            // cout << "4" << endl;
            nV.push_back(img.at<uchar>(j, i_m_1));
        }
    }

    return nV;
}

void setNeighbors(Mat &img, int j, int i, uchar val) {
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

    uchar *pRow = img.ptr(j_m_1);
    pRow[i_p_1] = val;
    pRow[i] = val;
    pRow[i_m_1] = val;

    pRow = img.ptr(j);
    pRow[i_m_1] = val;
}

void findContours(Mat &src, Mat &dst, int matchValue = 255) {
    // Mat tmp = src.clone();

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pDst = dst.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            if (*pSrc == matchValue) {
                // foreground
                std::vector<int> naybrs = getNeighbors(src, col, row);
                for (int b = 0; b < naybrs.size(); ++b) {
                    if (naybrs.at(b) == 0) {
                        *pDst = 255;
                        break;
                    } else {
                        *pDst = 0;
                    }
                }
            }
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pDst++;
        }
    }
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

// More or less gaussianBlur
void gaussianBlur(Mat &src) {
    Mat tmp = src.clone();

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pDst = tmp.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            std::vector<int> naybrs = getNeighbors(src, col, row);
            int myVal = *pDst;
            *pDst =    (3 * naybrs.at(0) +
                        1 * naybrs.at(1) +
                        3 * naybrs.at(2) +
                        1 * naybrs.at(3) +
                        3 * naybrs.at(4) +
                        1 * naybrs.at(5) +
                        3 * naybrs.at(6) +
                        1 * naybrs.at(7) +
                        5 * myVal) / 21.0;
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pDst++;
        }
    }
    tmp.copyTo(src);
}


void printVector(std::vector<int> vec) {
    cout << "printing vector" << endl;
    cout << "|";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << "|";
    }
    cout << endl;
}

void connectedRegions(Mat &src, int matchValue = 255) {
    Mat tmp = src.clone();
    Size size = src.size();
    Mat labels = Mat::zeros(size, CV_8UC1);
    int curLabel = 50;
    std::map < int, std::vector<int> > linked;

    for (int row = 0; row < src.rows; ++row) {
        uchar *pSrc = src.ptr(row);
        uchar *pLabel = labels.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            // match found, check neighbor labels and label it.
            if ( *pSrc == matchValue ) {
                // get neighbor labels
                std::vector<int> naybrs = getNeighbors(labels, col, row, 1);

                if (naybrs.size() != 0) {
                    int min = *min_element(naybrs.begin(), naybrs.end());
                    *pLabel = min;


                    for (int b = 0; b < naybrs.size(); ++b) {
                        // cout << "min: " << min << endl;
                        std::vector<int> destVec;

                        // auto result = std::find(curLabelVec.begin(), curLabelVec.end(), b);

                        // if (result == curLabelVec.end()) {
                        //     // the value b is not in linked[curLabel], so add
                        //     linked[naybrs[b]].push_back(b);
                        //     printVector(linked[naybrs[b]]);
                        // }
                        //
                        // vector<int>::iterator it;
                        set_union(linked[naybrs[b]].begin(), linked[naybrs[b]].end(),
                                  naybrs.begin(), naybrs.end(),
                                  back_inserter(destVec));
                        // for (const auto & i : destVec) {
                        //     std::cout << i << ' ';
                        // }
                        // std::cout << '\n';

                        linked[naybrs[b]].clear();
                        linked[naybrs[b]].assign(destVec.begin(), destVec.end());
                    }
                } else {
                    // cout << "no neighbors at " << col << ", " << row << endl;
                    linked[curLabel].push_back(curLabel);
                    *pLabel = curLabel;
                    curLabel += 50;
                }
            }
            *pSrc++;  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
            *pLabel++;
            // curLabel += 50;
        }
    }



    for (int row = 0; row < src.rows; ++row) {
        // cout << "rows" << endl;
        uchar *pSrc = src.ptr(row);
        uchar *pDst = labels.ptr(row);
        for (int col = 0; col < src.cols; ++col) {
            // cout << "val: " << (int)*pSrc << endl;
            // cout << matchValue << endl;
            // match found, check neighbor labels and label it.
            if ( (int)*pSrc == matchValue ) {
                // cout << "match" << endl;
                for (int i = 0; i < linked.size(); ++i) {
                    for (int j = 0; j < linked[i].size(); ++j)
                    {
                        // cout << "pDst: " << (int)*pDst << endl;
                        // cout << "linked[i][j]: " << (int)linked[i][j] << endl;
                        if (linked[i][j] == *pDst) {
                            // cout << "*min_element(linked[i].begin(), linked[i].end()): " << (int)*min_element(linked[i].begin(), linked[i].end()) << endl;
                            *pDst = *min_element(linked[i].begin(), linked[i].end());
                            // cout << "pDst: " << (int)*pDst << endl;
                        }
                    }
                }
            }
            *pDst++;
            *pSrc++;
        }
    }

    labels.copyTo(src);
}