#include <classifier.h>
#include <iostream>
using namespace std;

/** 
 * Generates a model for each number for the training stage. 
 * @param IN pathTraining: Path of the directory that contents the images for the training.
 * @param OUT models: A vector of images. Each element of the vector stores the model for each number.
 *
 * @return int value is returned. -1 if an error occurs, 0 otherwise.
 **/
int readModels(string pathTraining, vector<cv::Mat> *models) 
{
    int ret = 0;
    char nameRead[500];
    const int NUM_MODELS = 10;//number of models
    //names of the folders that contains the images for the training
    string folder[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};    
    models->clear();//clear the vector of models

    //generate a model for each number
    for (int i = 0; i < NUM_MODELS; i++) 
    {
        sprintf(nameRead, "%s/%s.bmp", pathTraining.data(), folder[i].data());
        cv::Mat imgModel8 = cv::imread(nameRead, CV_LOAD_IMAGE_GRAYSCALE);
        if (imgModel8.empty()) 
        {
            printf("Error reading %s\n", nameRead);
            ret = -1;
        }else{
            models->push_back(imgModel8);
        }
    }
    return ret;
}


/** 
 * Classify an image with a number.
 * @param IN imgIn: The image with the number to classify. Image of type CV_8UC1.
 * @param IN models: Vector of images with the number models. Images of type CV_8UC1.
 *
 * @return int value is returned. It corresponds to the best correlation number
 **/
int classifyCharacter(cv::Mat imgIn, vector<cv::Mat> models) 
{
    int ret = -1;
    int i=0;
    cv::Mat imgOutResize;
    cv::Mat imgOutTempl;
    double max[10];
    double min[10];
    double min1=200;
    double max1=0;
    int pos_min=0;
    int pos_max=0;
    
    
    for(i=0;i<models.size();i++)
    {
      cv::resize(imgIn, imgOutResize, cv::Size(CHAR_W,CHAR_H), 0, 0);
      cv::matchTemplate(imgOutResize, models.at(i), imgOutTempl, CV_TM_SQDIFF_NORMED);
      cv::minMaxLoc(imgOutTempl, &min[i], &max[i]);
    }
    
    for(i=0;i<10;i++)
    {
      if(min1>=min[i])
      {
        min1=min[i];
        pos_min=i;
      }
    }
    
    for(i=0;i<10;i++)
    {
      if(max1<=max[i])
      {
        max1=max[i];
        pos_max=i;
      }
    }
    
    //printf("pos_max:%d, pos_min:%d\n",pos_max, pos_min);
    
    ret=pos_min;
    
    return ret;

}
