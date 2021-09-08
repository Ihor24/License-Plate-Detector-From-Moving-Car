#include <cstdlib>
#include <colors.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int cvt_Bayer_RGB(cv::Mat imgBayer, cv::Mat *imgRGB) {
  //convertir a RGB y mostrar resultado
  cv::cvtColor(imgBayer, *imgRGB, cv::COLOR_BayerBG2BGR);
 
  imshow("Imagen RGB",*imgRGB);
  imwrite("./dat/RGB.png", *imgRGB);
  
  
  //separar los canales con split y mostrarlos por separado
  vector<cv::Mat> canales(3);
  cv:split(*imgRGB, canales);
  cv::imshow("B", canales.at(0));
  cv::imshow("G", canales.at(1));
  cv::imshow("R", canales.at(2));



  return 0;
}


int cvt_Bayer_HSV(cv::Mat imgBayer, cv::Mat *imgHSV) {
  //convertir a HSV y mostrar resultado
  // ..
  
  //separar los canales con split y mostrarlos por separado
  // ..

  // asignar la imagen HSV al segundo parametro de entrada

  return 0;
}

// OPCIONAL
// int cvt_Bayer_XYZ (cv::Mat imgBayer, cv::Mat *imgXYZ)
// int cvt_Bayer_Lab (cv::Mat imgBayer, cv::Mat *imgLAB)
// int cvt_Bayer_Luv (cv::Mat imgBayer, cv::Mat *imgLUV)
// int cvt_Bayer_YCrCb (cv::Mat imgBayer, cv::Mat *imgYCrCb)


