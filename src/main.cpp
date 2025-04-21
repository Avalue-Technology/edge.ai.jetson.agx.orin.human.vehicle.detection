#include "chrono"
#include "opencv2/opencv.hpp"
#include "yolov8.hpp"

using namespace std;
using namespace cv;

#define VIDEO

cv::Size       im_size(640, 640);
const int      num_labels  = 80;
const int      topk        = 100;
const float    score_thres = 0.25f;
const float    iou_thres   = 0.65f;

int main(int argc, char** argv)
{
    float    f;
    float    FPS[16];
    int      i, Fcnt=0, frame_skip = 2; // Skip every nth frame, change this value
    cv::Mat  image;
    std::chrono::steady_clock::time_point Tbegin, Tend;

    if (argc < 3) {
        fprintf(stderr,"Usage: ./YoloV8_RT [model_trt.engine] [image or video path] \n");
        return -1;
    }
    const string engine_file_path = argv[1];
    const string imagepath = argv[2];
    const string x = argv[3];
    const string y = argv[4];
    
    for(i=0;i<16;i++) FPS[i]=0.0;

    cout << "Set CUDA...\n" << endl;

    cudaSetDevice(0);

    cout << "Loading TensorRT model " << engine_file_path << endl;
    cout << "\nWait a second...." << std::flush;
    auto yolov8 = new YOLOv8(engine_file_path);

    cout << "\rLoading the pipe... " << string(10, ' ')<< "\n\r" ;
    cout << endl;
    yolov8->MakePipe(true);

#ifdef VIDEO
    VideoCapture cap(imagepath);
    if (!cap.isOpened()) {
        cerr << "ERROR: Unable to open the stream " << imagepath << endl;
        return 0;
    }
#endif // VIDEO
    int frame_count = 0;
    while(1){
#ifdef VIDEO
        cap >> image;
        if (image.empty()) {
            // When the video ends, reset to the first frame (looping)
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap >> image; // Grab the first frame again
        }

        // Skip frames by checking if frame_count is divisible by frame_skip
        if (frame_count % frame_skip != 0) {
            frame_count++;
            continue; // Skip this frame
        }
#else
        image = cv::imread(imagepath);
#endif
        yolov8->CopyFromMat(image, im_size);

        std::vector<Object> objs;

        Tbegin = std::chrono::steady_clock::now();
        yolov8->Infer();
        Tend = std::chrono::steady_clock::now();

        yolov8->PostProcess(objs, score_thres, iou_thres, topk, num_labels);
        yolov8->DrawObjects(image, objs);

        // Calculate frame rate
        f = std::chrono::duration_cast <std::chrono::milliseconds> (Tend - Tbegin).count();
        if(f>0.0) FPS[((Fcnt++)&0x0F)]=1000.0/f;
        for(f=0.0, i=0;i<16;i++){ f+=FPS[i]; }
        putText(image, cv::format("FPS %0.2f", f/8),cv::Point(20,40),cv::FONT_HERSHEY_COMPLEX,1.2, cv::Scalar(0, 0, 255));

        // Set the window properties (resize and move)
        cv::namedWindow("Use Yolov8 Model", cv::WINDOW_NORMAL); // Allows resizing
        cv::resizeWindow("Use Yolov8 Model", 960, 480); // Resize window
        cv::moveWindow("Use Yolov8 Model", std::stoi(x), std::stoi(y)); // Move window to (100, 100)
        // Show output
        imshow("Use Yolov8 Model", image);
        char esc = cv::waitKey(1);
        if(esc == 27) break;

        frame_count++; // Increment frame count
    }
    cv::destroyAllWindows();

    delete yolov8;

    return 0;
}

