//
// Created by liu on 23-5-4.
//

#ifndef OPENVINO_TEST_OPENVINOINFER_H
#define OPENVINO_TEST_OPENVINOINFER_H

#include <opencv2/opencv.hpp>
#include <openvino/openvino.hpp>
#include <vector>

//#define num

//用前先根据模型修改好要修改的地方

using namespace cv;
using namespace std;
class OpenvinoInfer {
#ifdef num
    const int IMAGE_HEIGHT = 32;
    const int IMAGE_WIDTH = 32;
#else
    const int IMAGE_HEIGHT = 640;
    const int IMAGE_WIDTH = 640;
#endif
    std::shared_ptr<ov::Model> model;
    ov::Core core;
    ov::preprocess::PrePostProcessor *ppp;
    ov::CompiledModel compiled_model;
    ov::Shape input_shape;
public:
    OpenvinoInfer(string model_path, string device){
#ifdef num
        input_shape = {1, static_cast<unsigned long>(IMAGE_HEIGHT), static_cast<unsigned long>(IMAGE_WIDTH), 1};
#else
        input_shape = {1, static_cast<unsigned long>(IMAGE_HEIGHT), static_cast<unsigned long>(IMAGE_WIDTH), 1};
#endif
        model = core.read_model(model_path);
        // Step . Inizialize Preprocessing for the model
        ppp = new ov::preprocess::PrePostProcessor(model);
//        // Specify input image format
#ifdef num
        ppp->input().tensor().set_shape(input_shape).set_element_type(ov::element::u8).set_layout("NHWC");
        ppp->input().preprocess().resize(ov::preprocess::ResizeAlgorithm::RESIZE_LINEAR);
        ppp->input().model().set_layout("NHWC");
#else
        ppp->input().tensor().set_element_type(ov::element::u8).set_layout("NHWC").set_color_format(ov::preprocess::ColorFormat::BGR);
        // Specify preprocess pipeline to input image without resizing
        ppp->input().preprocess().convert_element_type(ov::element::f32).convert_color(ov::preprocess::ColorFormat::RGB).scale({255., 255., 255.});
        //  Specify model's input layout
        ppp->input().model().set_layout("NCHW");
#endif
        // Specify output results format
        ppp->output().tensor().set_element_type(ov::element::f32);
        // Embed above steps in the graph
        model = ppp->build();

        compiled_model = core.compile_model(model, device);
    }

    void infer(Mat img){
        // Step 3. Read input image
        // resize image
        resize(img,img,Size(IMAGE_WIDTH,IMAGE_HEIGHT));


        // Step 5. Create tensor from image
        int rows = img.rows;
        int cols = img.cols;

        uchar* input_data = (uchar *)img.data; // 创建一个新的float数组

        ov::Tensor input_tensor = ov::Tensor(compiled_model.input().get_element_type(), compiled_model.input().get_shape(), input_data);


        // Step 6. Create an infer request for model inference
        ov::InferRequest infer_request = compiled_model.create_infer_request();
        infer_request.set_input_tensor(input_tensor);
        double ta = cv::getTickCount();
        infer_request.infer();
        double tb = cv::getTickCount();
        std::cout <<"timeab: "<< (tb - ta) / cv::getTickFrequency() * 1000 << " "<<std::endl;

        //Step 7. Retrieve inference results
        const ov::Tensor &output_tensor = infer_request.get_output_tensor();
        ov::Shape output_shape = output_tensor.get_shape();
        float *detections = output_tensor.data<float>();

        // Step 8. get result
        int res = 0;
        for(int i = 0; i < 10; i++){
//            std::cout<<detections[i]<<endl;
            if(detections[i] == 1){
                res = i;
            }
        }
        cout<<"num: "<<res<<endl;
    }
    ~OpenvinoInfer(){
//        delete ppp;
    }
};


#endif //OPENVINO_TEST_OPENVINOINFER_H
