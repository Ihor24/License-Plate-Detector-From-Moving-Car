#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#define CHAR_W 14
#define CHAR_H 24

int readModels(string pathTraining, vector<cv::Mat> *models);
int classifyCharacter(cv::Mat imgIn, vector<cv::Mat> models);

#endif /* _CLASSIFIER_H_ */
