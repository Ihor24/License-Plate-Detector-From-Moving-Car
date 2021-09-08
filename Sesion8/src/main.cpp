#include <cstdlib>
#include <fotoDetector.h>

using namespace std;

int main(int argc, char** argv) 
{
    int ret = 0;
    int frame = 0;
    char name[500];
    char nombre_imgNow[100];

    //check input parameters
    if (argc != 4) 
    {
        printf("\n Type the name of the video and its size (width height)\n");
        printf("\n      Example: %s ./dat/video.raw 320 240\n", argv[0]);
        ret = -1;
    }
    else 
    {
        //open the video
        FILE *fd = fopen(argv[1], "rb");
        if (fd == NULL) {
            printf("Error reading file: %s\n", argv[1]);
            ret = -1;
        } 
        else 
        {
            //init variables
            int width = atoi(argv[2]);
            int height = atoi(argv[3]);            
            cv::Mat imgNow = cv::Mat(height, width, CV_8UC1);//current frame
            cv::Mat imgPrev = cv::Mat(height, width, CV_8UC1);//previous frame
            cv::Mat imgColor;//color image to paint the results
            int state = CAR_NOT_DETECTED;//state of the system            
            cv::Scalar colorPlate = CV_RGB(0, 255, 0);//color for the plate
            cv::Scalar colorChar = CV_RGB(255, 0, 0);//color for the numbers

            //init the previous frame
            fread(imgPrev.data, sizeof (unsigned char), width * height, fd);
            //read a new frame
            while (fread(imgNow.data, sizeof (unsigned char), width * height, fd)) 
            {
                static int cnt_state=0;
                static int cnt_state2=0;
                frame++;                                                            
                cv::imshow(argv[1],imgNow);
                cv::waitKey(33);

                //Llamar a la función carDetected (imagen en t, imagen en t-1, estado por referencia)
                carDetected(imgNow, imgPrev, &state);
                // Si la función devuelve 1, guardar la imagen y hacer un waitKey(0)
                //printf("\nState: %d; cnt:%d\n", state,cnt_state);

                if(state == 0){cnt_state++;}
                if(state == 1 && cnt_state >= 2){cnt_state2++;}
                if(cnt_state >= 2 && state == 1 && cnt_state2 <= 2)
                {
                    cnt_state = 0;

                    sprintf(nombre_imgNow, "./dat/foto000%d.png",cnt_state2);
                    imshow(nombre_imgNow, imgNow);
                    cv::imwrite(nombre_imgNow, imgNow);
                    cv::waitKey(0);

                }

                //update images
                imgNow.copyTo(imgPrev);
            }
            fclose(fd);
        }
    }

    return ret;
}
