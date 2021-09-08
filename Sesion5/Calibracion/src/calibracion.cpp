#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <ostream>
#include <iostream>

#define BOARD_VERT_CORNERS 6
#define BOARD_HORZ_CORNERS 8
#define NUM_IMAGES 10
#define SQUARE_SIZE 2.8 //cm

/* Programa de calibración que usa 10 imagenes, de nombre imagen0000.png hasta
imagen0009.png; con patron de calibracion de 8x6 esquinas con cuadrados de 2.8cm*/

using namespace std;

int main(int argc, char** argv) 
{
    
    vector<cv::Mat> imgCalib(NUM_IMAGES); //Vector para almacenar las imagenes originales de calibracion
    vector<cv::Mat> imgColorCorners(NUM_IMAGES); //Vector para almacenar las imagenes con las esquinas dibujadas (color)
    vector<cv::Mat> imgUndist(NUM_IMAGES); //Vector para almacenar las imagenes corregidas (sin distorsion)
    
    cv::Size board_size = cv::Size(BOARD_VERT_CORNERS, BOARD_HORZ_CORNERS); //Numero de esquinas en el chessboard vertical x horizontal
    vector<vector<cv::Point2f> > imgCorners(NUM_IMAGES); //Vector para almacenar las esquinas detectadas en cada imagen
    vector<vector<cv::Point3f> > chessboardCorners(1); //Vector para almacenar las posiciones de las esquinas en el chessboard real (espacio de coordenadas del chessboard)
    
    cv::Mat camMatrix, distCoeff; //Matrices para almacenar los parametros de calibracion
    vector<cv::Mat> rvecs, tvecs;  //Vectores para almacenar los vectore de rotacion y traslacion
    
    char nombreImagen[100];
    int ret = 0, error=0;

    for (int i = 0; i < NUM_IMAGES; i++) 
    {
        //Leer la imagen de calibracion i
        sprintf(nombreImagen, "./dat/imagen%04d.png", i);
        imgCalib.at(i) = cv::imread(string(nombreImagen), cv::IMREAD_GRAYSCALE);

        //Mostrar la imagen de calibracion i
        imshow(nombreImagen , imgCalib.at(i));

        //Comprobar si la imagen se ha leido correctamente
        if (imgCalib.at(i).empty())
        {
            //Si hay error no hacemos nada con la imagen
            printf("Error reading image %s\n", nombreImagen);
            ret = -1; 
        }
        else
        {
            //Si la imagen se ha leido correctamente: Buscamos las esquinas en la imagen, las mostramos y guardamos la imagen con las esquinas
            //Detectar las esquinas en la imagen i
            error = cv::findChessboardCorners(imgCalib.at(i), board_size, imgCorners.at(i), cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS | cv::CALIB_CB_FAST_CHECK);

            //Comprobar que las esquinas se han detectado correctamente
            if (!error)
            {
              cout << "\n\rError al detectar las esquinas en imagen %d \n\r" << i <<endl;
              return -1;
            }
            
            else
            {

            //Mejorar la deteccion (subpixelica)
            cv::cornerSubPix(imgCalib.at(i), imgCorners.at(i), cv::Size(5,5), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1));

            //Convertir la imagen leida a color para poder dibujar las esquinas
            cv::cvtColor(imgCalib.at(i), imgColorCorners.at(i), cv::COLOR_GRAY2BGR);
            
            //Dibujar las esquinas detectas en la imagen a color
            cv::drawChessboardCorners(imgColorCorners.at(i), board_size, imgCorners.at(i), error);

            //Guardar la imagen con las esquinas dibujadas en el directorio ./dat con nombre sprintf(nombreImagen,"./dat/imagen%04dColor.png", i);
            
            sprintf(nombreImagen, "./dat/imagen%04dColor.png", i);
            imshow(nombreImagen, imgColorCorners.at(i));
            imwrite(nombreImagen, imgColorCorners.at(i));
            cv::waitKey(0);
            }
        }
    }

    //Rellenar el vector con las posiciones reales de las esquinas del patron
    for (int r=0; r < board_size.height; r++)
    {
      for (int c=0; c< board_size.width; c++)
      {
       chessboardCorners.at(0).push_back(cv::Point3f(float(c*SQUARE_SIZE),float(r*SQUARE_SIZE),0));
      }
    }
    

    //Replicar las mismas posiciones para todas las imagenes porque se usa el mismo patron en todas
    chessboardCorners.resize(imgCalib.size(),chessboardCorners.at(0));

    //Calibrar la camara y mostrar por pantalla los parametros de calibracion
    cv::calibrateCamera(chessboardCorners, imgCorners, board_size, camMatrix, distCoeff, rvecs, tvecs);
    

    std::cout << "Camera Matrix:\n" << camMatrix << std::endl;
    std::cout << "disCoeff:\n" << distCoeff << std::endl;

    //Transformar todas las imagenes para compensar la distorsion y guardarlas
    

    for (int z=0; z<NUM_IMAGES; z++)
    {
     //Leer la imagen de calibracion i
     sprintf(nombreImagen, "./dat/imagen%04d.png", z);
     imgCalib.at(z) = cv::imread(string(nombreImagen), cv::IMREAD_GRAYSCALE);

     //Mostrar la imagen de calibracion i
     imshow(nombreImagen, imgCalib.at(z));


    //Arreglo la distorsion
     cv::undistort(imgCalib.at(z), imgUndist.at(z), camMatrix, distCoeff);

     //Muestro y guardo el arreglo
     sprintf(nombreImagen, "./dat/imagen%04dUndist.png", z);
     imshow(nombreImagen, imgUndist.at(z));
     imwrite(nombreImagen, imgUndist.at(z));
     cv::waitKey(0);
    }
    
    //////////////////////////////////////////////IMAGEN COCHE//////////////////////////////////////////////////////////
    
    sprintf(nombreImagen, "./dat/coche7cm_40cm.png");
    imgCalib.at(0) = cv::imread(string(nombreImagen), cv::IMREAD_GRAYSCALE);

    //Mostrar la imagen del coche
    imshow(nombreImagen , imgCalib.at(0));
    

    //Replicar las mismas posiciones para todas las imagenes porque se usa el mismo patron en todas
    chessboardCorners.resize(imgCalib.size(),chessboardCorners.at(0));

    //Calibrar la camara y mostrar por pantalla los parametros de calibracion
    cv::calibrateCamera(chessboardCorners, imgCorners, board_size, camMatrix, distCoeff, rvecs, tvecs);
    

    std::cout << "Camera Matrix:\n" << camMatrix << std::endl;
    std::cout << "disCoeff:\n" << distCoeff << std::endl;

    //Transformar imagen para compensar la distorsion y guardarla
    cv::undistort(imgCalib.at(0), imgUndist.at(0), camMatrix, distCoeff);

     //Muestro y guardo el arreglo
     sprintf(nombreImagen, "/home/l8/Escritorio/Sesion5/Cursor/coche_calibrado.png");
     imshow(nombreImagen, imgUndist.at(0));
     imwrite(nombreImagen, imgUndist.at(0));
     cv::waitKey(0);
    

    return ret;
}
