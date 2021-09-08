#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <colors.h>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    FILE *pf_video = NULL;
    int numCols = 640, numRows = 480;
    char key = '1';
    string windowName = "Imagen Bayer";

    if (argc != 4) {
        printf("\n Introduzca el nombre del video, y el tamaño (ancho y alto)\n");
        printf("\n      Ejemplo: ./lee video.raw 640 480\n");
        ret = -1;
    } else {

        pf_video = fopen(argv[1], "r");
        if (pf_video == NULL) {
            printf("Error al leer el video: %s\nCompruebe el nombre del fichero y su ruta\n", argv[1]);
            ret = -1;
        } else {
            numCols = atoi(argv[2]);
            numRows = atoi(argv[3]);
            cv::Mat imageVideo = cv::Mat(numRows, numCols, CV_8UC1);
            cv::Mat imageVideoRGB = cv::Mat(numRows, numCols, CV_8UC3);

            while ((fread(imageVideo.data, sizeof (unsigned char), numRows * numCols, pf_video)) > 0 && key != 'Q') {
                switch (key) {
                    case '1': 
                        // mostrar imagen Bayer y grabar en "./dat/BAYER.png"
                        
                        cv::namedWindow(windowName);
                        imshow(string(argv[1]),imageVideo);
                        imwrite("./dat/BAYER.png", imageVideo);
												
                        break;
                    case '2':
                        // llamar a la funcion de conversion Bayer a RGB y guardar resultado en "./dat/RGB.png"
                        cvt_Bayer_RGB(imageVideo, &imageVideoRGB);
                        
                        break;
                    /*case '3':                        
                        // llamar a la funcion de conversion Bayer a HSV y guardar resultado en "./dat/HSV.png"
                        break;
                    case '4': // opcional
                        // llamar a la funcion de conversion Bayer a XYZ y guardar resultado en "./dat/XYZ.png"
                        break;
                    case '5': // opcional
                        // llamar a la funcion de conversion Bayer a LAB y guardar resultado en "./dat/LAB.png"
                        break;
                    case '6': // opcional            
                        // llamar a la funcion de conversion Bayer a LUV y guardar resultado en "./dat/LUV.png"
                        break;
                    case '7': // opcional
                        // llamar a la funcion de conversion Bayer a YCrCb y guardar resultado en "./dat/TCrCb.png"
                        break;*/
                }
                char aux = cv::waitKey(0);
                key = toupper(aux);
            }
            fclose(pf_video);
        }
    }
    return ret;
}
