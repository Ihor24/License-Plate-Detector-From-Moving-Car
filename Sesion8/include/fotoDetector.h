#ifndef _PHOTODETECTOR_H_
#define _PHOTODETECTOR_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#define CAR_NOT_DETECTED 0
#define CAR_DETECTED 1
    
bool analyseRoi(cv::Mat img, cv::Rect roi, double thres);
bool carDetected(cv::Mat imgNow, cv::Mat imgPrev, int *state);

#endif /* _PHOTODETECTOR_H_ */
