#ifndef _PLATE_H_
#define _PLATE_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

// Funcion detectPlate
//     Parametros de entrada:
//       - cv::Mat imagenIn --> Imagen de Entrada
//       - vector<cv::Rect> *matriculas --> lista de matriculas detectadas
int detectPlate(cv::Mat imgIn, vector<cv::Rect> *position);

#endif /* _PLATE_H_ */
