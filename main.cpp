#include <opencv2/dnn.hpp>
#include <openvino/openvino.hpp>
#include <opencv2/opencv.hpp>
#include "OpenvinoInfer.h"

using namespace std;


int main(){
    string model_path = "../model/v20_gamma_64_641.xml";
    OpenvinoInfer openvinoInfer(model_path,"CPU");
    Mat img = imread("../imgs/3.jpg");
    cvtColor(img,img,cv::COLOR_BGR2GRAY);
    openvinoInfer.infer(img);
    return 0;
}