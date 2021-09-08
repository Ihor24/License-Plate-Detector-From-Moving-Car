#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace std;

void on_mouse(int event, int x, int y, int flags, void* param) {
    printf("Mouse Pointer (u,v): (%d, %d)\r", x, y);
    fflush(stdout);
}

int main(int argc, char** argv) {
    int ret = 0;

    if (argc!=2)
    {
        printf("Error: El programa necesita recibir la imagen como parametro de entrada\nUso: %s imagen\n", argv[0]);
        ret = -1;
    }else{
        cv::Mat imgClick = cv::imread(string(argv[1]), cv::IMREAD_GRAYSCALE);
        if (imgClick.empty()) {
            printf("Error reading %s\n", argv[1]);
            ret = -1;
        } else {
            cv::imshow(string("Image"), imgClick);
            cv::setMouseCallback(string("Image"), on_mouse, NULL);
            cv::waitKey(0);
        }
    }
    return ret;
}
