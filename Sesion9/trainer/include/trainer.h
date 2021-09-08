#ifndef _TRAINER_H_
#define _TRAINER_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#define CHAR_W 14
#define CHAR_H 24

int generateModel_training(string pathTraining, vector<cv::Mat> *models);
int preProcessing(cv::Mat imgIn8, cv::Mat *imgOut32, int imgOutW, int imgOutH);

#endif /* _TRAINER_H_ */
