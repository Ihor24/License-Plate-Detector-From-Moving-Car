#include <trainer.h>
#include <iostream>
using namespace std;

/** 
 * Generates a model for each number for the training stage. 
 * @param IN pathTraining: Path of the directory that contents the images for the training.
 * @param OUT models: A vector of images. Each element of the vector stores the model for each number.
 *
 * @return int value is returned. -1 if an error occurs, 0 otherwise.
 **/
int generateModel_training(string pathTraining, vector<cv::Mat> *models) 
{
    int ret = 0;
    char nameRead[500], nameWrite[500];
    const int NUM_IMAGES = 20;//number of images for each model
    const int NUM_MODELS = 10;//number of models
    //names of the folders that contains the images for the training
    string folder[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};    
    models->clear();//clear the vector of models

    //generate a model for each number
    for (int i = 0; i < NUM_MODELS; i++) 
    {
        //image to accumulate the current model images
        cv::Mat imgSum32 = cv::Mat::zeros(CHAR_H, CHAR_W, CV_32FC1);

        //read the images of each model
        for (int j = 0; j < NUM_IMAGES; j++) 
        {
            sprintf(nameRead, "%s/%s/%s_%d.bmp", pathTraining.data(), folder[i].data(), folder[i].data(), j + 1);
            cv::Mat imgTrain8 = cv::imread(nameRead, CV_LOAD_IMAGE_GRAYSCALE);
            if (imgTrain8.empty()) 
            {
                printf("Error reading %s\n", nameRead);
                ret = -1;
            } else {
                //the images for the training have blank space around the number and should be deleted
                cv::Mat imgFiltered;//image that contains only the number
                preProcessing(imgTrain8, &imgFiltered, CHAR_W, CHAR_H);
                //accumulate the image value
                cv::add(imgSum32, imgFiltered, imgSum32);
            }
        }
        //compute mean value of the images
        cv::Mat imgMean8;
        imgSum32.convertTo(imgMean8, CV_8UC1, 1.0 / NUM_IMAGES);
        //save the model to disk
        sprintf(nameWrite, "%s/models/%s.bmp", pathTraining.data(), folder[i].data());        
        cv::imwrite(nameWrite, imgMean8);
        //store the model in the model vector
        models->push_back(imgMean8);
    }

    return ret;
}

/** 
 * Detects an object in the image and resize it to the desired size.
 * @param IN imgIn8: The current training image. Image of type CV_8UC1.
 * @param OUT imgOut32: Resized image of the number. Image of type CV_32FC1.
 * @param IN imgOutW: Desired width of imgOut32
 * @param IN imgOutH: Desired height of imgOut32
 *
 * @return int value is returned. -1 if an error occurs, 0 otherwise.
 **/
int preProcessing(cv::Mat imgIn8, cv::Mat *imgOut32, int imgOutW, int imgOutH) 
{
    int ret = 0;
    int marginV = 1;//margin up and above the number
    int marginH = 2;//margin on the left and right sides of the number
    
    //vertical and horizontal projections
    cv::Mat vertSum, horizSum;
    cv::reduce(imgIn8, vertSum, 0, CV_REDUCE_SUM, CV_32FC1);
    cv::reduce(imgIn8, horizSum, 1, CV_REDUCE_SUM, CV_32FC1);
    
    //crop the number
    float maxValV = 255 * imgIn8.rows;
    float maxValH = 255 * imgIn8.cols;
    bool found = false;
    int x = 0, y = 0, w = 0, h = 0;
    for (int i = 0; i < vertSum.cols && !found; i++) 
    {
        found = (vertSum.at<float>(0, i) >= maxValV) && i > 2;
        w = i;
    }
    found = false;
    for (int i = 0; i < horizSum.rows && !found; i++) 
    {
        found = (horizSum.at<float>(i, 0) >= maxValH) && i > 2;
        h = i;
    }
    //select the region
    cv::Mat roiNumber = imgIn8(cv::Rect(x, y, w, h));
    //add a margin to the region
    cv::Mat imgMargin = cv::Mat(roiNumber.rows + 2 * marginH, roiNumber.cols + 2 * marginV, CV_8UC1, 255);
    cv::Mat roiTmp = imgMargin(cv::Rect(marginV, marginH, w, h));
    roiNumber.copyTo(roiTmp);
    //resize imgMargin to the size we want
    cv::Mat imgMargin32, imgResized;
    imgMargin.convertTo(imgMargin32, CV_32FC1);
    cv::resize(imgMargin32, imgResized, cv::Size(imgOutW, imgOutH));

    *imgOut32 = imgResized;
    return ret;
}
