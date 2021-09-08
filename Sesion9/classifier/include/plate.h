#ifndef _PLATE_H_
#define _PLATE_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int detectPlate(cv::Mat imgIn,vector<cv::Rect> *position);



#endif /* _PLATE_H_ */
