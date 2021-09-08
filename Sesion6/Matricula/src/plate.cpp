#include <cstdlib>
#include <plate.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int detectPlate(cv::Mat imgIn, vector<cv::Rect> *position) 
{
    int ret = 0;

    //Detectar bordes usando Canny 
    cv::Mat imgCanny;
    cv::Mat imgColor;
    double thresLow = 85; 
    double thresHigh = 105; 
    int aperture = 3;
    char nombreImagen_Canny[100];
    char nombreImagen_Color[100];
    char nombreImagen_Contornos[100];
    
    // llamar funcion canny
    cv::Canny(imgIn, imgCanny, thresLow, thresHigh, aperture);

    // mostrar resultado de la deteccion de bordes 
    sprintf(nombreImagen_Canny, "./dat/imagen_canny4.png");
    imshow(nombreImagen_Canny, imgCanny);
    imwrite(nombreImagen_Canny, imgCanny);
    cv::waitKey(0);
    
    //Elimino contorno de imagen
    cv::rectangle(imgCanny, cv::Rect(0,0,imgIn.cols, imgIn.rows),  CV_RGB(0,0,0),8 ,8,0 );

    // buscar contornos
    vector<vector<cv::Point> > contours; //Donde van a estar almacenados los contornos
    
    
    cv::findContours(imgCanny, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // dibujar todos los contornos en verde en imagen de color copia de la original y mostrarlos
    cv::cvtColor(imgCanny, imgColor, cv::COLOR_GRAY2RGB); //Convierto a color
    
    
    int i=0;
    for (i=0; i<contours.size(); i++)
    {
      cv::drawContours(imgColor, contours, i, CV_RGB(0,0,255), 1, 8);
    }
    sprintf(nombreImagen_Contornos, "./dat/imagen_contornos4.png");
    imshow(nombreImagen_Contornos, imgColor);
    imwrite(nombreImagen_Contornos, imgColor);
    cv::waitKey(0);
    
    

    // umbrales para analisis de contornos
    const double MIN_LENGTH = 190;
    const double MIN_AREA = 1000;
    const double MAX_RECTANGULARITY = 1;
    double aux_long;
    double aux_area;
    double aux_rect;

    // analizar todos los contornos, calculando perimetro, area y rectangularidad y aplicando restricciones
    for (i=0; i<contours.size(); i++)
    {
        aux_long = cv::arcLength(contours.at(i), true);
        aux_area = cv::contourArea(contours.at(i));
        aux_rect = aux_long/aux_area;

        if(aux_long>=MIN_LENGTH && aux_area>=MIN_AREA && aux_rect<=MAX_RECTANGULARITY)
        {
            cv::Rect boundRect = cv::boundingRect(contours.at(i));
            // cuando un contorno cumpla con las restricciones habra que guardarlo en la variable <<position>>
            //La función me devuelve el contorno
            position->push_back(boundRect);
        }

    }
    

    return ret;
}

