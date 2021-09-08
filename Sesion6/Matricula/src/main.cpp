#include <cstdlib>
#include <plate.h>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    cv::Mat imgColor;
    char NombreImagen[100];

    if (argc != 2) 
    {
        printf("Example: ./matricula ./dat/coche1.png\n\n");
        ret = -1;
    } else {
        cv::Mat imgGrey = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
        if (imgGrey.empty()) {
            printf("Error reading image %s\n", argv[1]);
            ret = -1;
        } else {           
            vector<cv::Rect> platePos;
            // Detectar matricula. La función detectPlate debe definirse en ./src/plate.cpp	
            detectPlate(imgGrey, &platePos);
            
            printf("%ld plates detected in image %s\n", platePos.size(), argv[1]);
	    
            // Dibujar rectángulos en color (en imagen imgColor que debe ser copia en color de imgGrey)

            cv::cvtColor(imgGrey, imgColor, cv::COLOR_GRAY2RGB); //Convierto a color

            int i=0;

            for(i=0; i<platePos.size(); i++)
            {
                cv::rectangle(imgColor, platePos.at(i), CV_RGB(255,0,0), 1, 8, 0);
            }


            sprintf(NombreImagen, "./dat/imagen_final4.png");
            imshow(NombreImagen, imgColor);
            imwrite(NombreImagen, imgColor);
            cv::waitKey(0);

        }
    }

    return ret;
}
