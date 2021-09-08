#include <cstdlib>
#include <plate.h>
#include <plateCharacters.h>
#include <classifier.h>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    int matricula[3];
    char matricula2[3];
    
    //check input parameters
    if (argc != 2) {
        printf("\n Error. Type the name of the image\n");
        printf("\n      Example: ./classifier ./dat/coche.png\n");
        ret = -1;
    } else {
        cv::Scalar colorPlate = CV_RGB(0, 255, 0); //color for the plate
        cv::Scalar colorChar = CV_RGB(255, 0, 0); //color for the numbers
        cv::Scalar color_caracteres=CV_RGB(255,255, 255);
        cv::Mat imgCoche = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
        if (imgCoche.empty()) {
            printf("Error reading image %s\n", argv[1]);
            ret = -1;
        } else {	  
            vector<cv::Mat> models;//vector with the models
            readModels("./dat/models/",&models);//read generated models  
            
            cv::Mat imgColor;
            cv::cvtColor(imgCoche, imgColor, cv::COLOR_GRAY2RGB);
            //detect the car plate
            vector<cv::Rect> plates;
            detectPlate(imgCoche, &plates);
            
            //draw each plate found
            for (unsigned int i = 0; i < plates.size(); i++) 
            {
                cv::rectangle(imgColor, plates.at(i), colorPlate, 1);
                vector<cv::Rect> charPos;
                vector<cv::Mat> charImages;
                detectCharacters(imgCoche, plates.at(i), &charPos, &charImages);
                //draw each character detected
                for (unsigned int j = 0; j < charImages.size(); j++) 
                {
                    cv::rectangle(imgColor, charPos.at(j), colorChar, 1);                    
                    // Clasificar cada caracter, mostrar el resultado por pantalla y escribir el numero de matricula sobre la imagen
                    matricula[j]=classifyCharacter(charImages.at(j), models);
                    
                    printf("Matricula:%d\n",matricula[j]);
       
                }
            }
          
            sprintf(matricula2, "Matricula:%d%d%d", matricula[0],matricula[1],matricula[2]);
            cv::putText(imgColor, matricula2, cv::Point(30,30), CV_FONT_HERSHEY_SIMPLEX, 1.0, CV_RGB(255,255,255), 1, 8);
            //cv::putText(imgColor, "hola", cv::Point(10, 10), CV_FONT_HERSHEY_SIMPLEX , color_caracteres);
            
            //save the results
            cv::imwrite("./dat/results.png", imgColor);
            cv::imshow("results", imgColor);
            cv::waitKey(0);
        }
    }
    return ret;
}
