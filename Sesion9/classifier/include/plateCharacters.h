#ifndef _PLATECHARACTERS_H_
#define _PLATECHARACTERS_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
int detectCharacters(cv::Mat imgIn, cv::Rect platePos, vector<cv::Rect> *characters, vector<cv::Mat> *charImages);
int removeNoise(cv::Mat imgIn, cv::Mat *imgOut);
int vertHorizProjection(cv::Mat imgIn, cv::Rect roiPos, int vertThres, int horizThres,vector<cv::Rect> *objects, vector<cv::Mat> *vecImages);



#endif /* _PLATECHARACTERS_H_ */
