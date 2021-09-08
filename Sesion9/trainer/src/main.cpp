#include <cstdlib>
#include <trainer.h>

using namespace std;

int main(int argc, char** argv) 
{
    int ret = 0;
    char nombreImagen[100];
    vector<cv::Mat> models8;//vector with the models
    
    generateModel_training("./dat",&models8);//generate the number models

    cv::namedWindow("results", CV_WINDOW_NORMAL);

    for (unsigned int i = 0; i< models8.size(); i++)
    {
      sprintf(nombreImagen, "/home/l8/Escritorio/classifier/dat/models/modelo%d.png", i);
      cv::imshow(nombreImagen, models8.at(i));
      cv::imwrite(nombreImagen, models8.at(i));
      cv::waitKey(0);      
    }

    return ret;
}
