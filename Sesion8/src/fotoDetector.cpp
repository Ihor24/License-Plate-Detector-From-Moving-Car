#include <fotoDetector.h>
#include <iostream>
using namespace std;

/** 
 * Analyses the ROI of the image and return a boolean value.
 * @param IN img: Image of type CV_8UC1 where the function sets the ROI. 
 * @param IN roi: Rectangle of the Region Of Interest.
 * @param IN thres: Value of the threshold
 *
 * @return bool value is returned. true if mean value of the ROI is greater than the threshold, false otherwise.
 **/
bool analyseRoi(cv::Mat img, cv::Rect roi, double thres) 
{
    cv::Mat imgRoi = img(roi);
    cv::Scalar meanVal = cv::mean(imgRoi);
    //printf("roiVal = %f / %lf\n",meanVal.val[0],thres);
    return meanVal.val[0] >= thres;
}

/** 
 * Detects when the vehicle is crossing the scene.
 * @param IN imgNow: Image of type CV_8UC1 of the current frame.
 * @param IN imgPrev: Image of type CV_8UC1 of the previous frame.
 * @param IN/OUT state: The state of the system can be CAR_DETECTED or CAR_NOT_DETECTED
 *
 * @return bool value is returned. true only the first time a vehicle is detected, false otherwise.
 **/
bool carDetected(cv::Mat imgNow, cv::Mat imgPrev, int *state) 
{

    const bool SHOW_IMAGES = false;
    int ret = false;
    cv::Mat imgColor, imgDiff, imgThres;
    cv::Scalar roiColor = CV_RGB(255, 0, 0);
    char nombre_imgDiff[100];
    char nombre_imgThres[100];
    char nombre_imgcolor[100];


    //define the area of analysis
    int xRoi = 80;
    int yRoi = 70;
    int wRoi = 60;
    int hRoi = 40;
    cv::Rect roiPos = cv::Rect(xRoi, yRoi, wRoi, hRoi);    
        
    // Obtener diferencia absoluta entre imgNow e imgPrev, guardarlo en imgDiff y VISUALIZAR
    cv::absdiff(imgNow, imgPrev, imgDiff);
    
    sprintf(nombre_imgDiff, "./dat/imagen_Diff.png");
    imshow(nombre_imgDiff, imgDiff);
    cv::imwrite(nombre_imgDiff, imgDiff);


    // Umbralizar (umbral global) imagen imgDiff, guardar resultado en imgThres y VISUALIZAR (definir umbral)
    cv::threshold(imgDiff, imgThres, 25, 100, 3);
    
    sprintf(nombre_imgThres, "./dat/imagen_threshold.png");
    imshow(nombre_imgThres, imgThres);
    cv::imwrite(nombre_imgThres, imgThres);


    
    // Dibujar ROI en ROJO en imgThres convertida a color en imgColor y VISUALIZAR
    cv::cvtColor(imgThres, imgColor, cv::COLOR_GRAY2RGB);
    cv::rectangle(imgColor, roiPos, roiColor, 1);
       
     
    sprintf(nombre_imgcolor, "./dat/imagen_rect.png");
    imshow(nombre_imgcolor, imgColor);
    cv::imwrite(nombre_imgcolor, imgColor);

    

    // Llamar a la funcion que evalua la media de nivel de gris de la ROI (definir el umbral)
    bool coche;
    coche = analyseRoi(imgThres, roiPos, 10);
    
    //printf(" Deteccion:%d\n ", coche);

    static int cont = 0;
    
    // Implementar maquina de estados con la variable 'state' en funcion de lo que devuelva 'analyseRoi' y para el caso de que se de la primera deteccion poner 'ret' a true
    switch(coche)
    {
        case 1:
            cont++;
            break;

        case 0:
            cont = 0;
            break;
    }
    
    if(cont == 1)
    {
        ret = true;
    }

    if(ret == true){*state = 1;}
    else{*state = 0;}


    //printf("Return: %d; cont: %d\n", ret, cont);


    return ret;
}
