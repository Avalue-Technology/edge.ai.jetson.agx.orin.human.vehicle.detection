# edge.ai.jetson.agx.orin.human.vehicle.detection
About Jetson AGX Orin AI Model - Human, Vehicle Detection Sample.
$ sudo apt-get update 
$ sudo apt-get upgrade
$ sudo apt-get install cmake wget curl
$ mkdir *MyDir*
$ cd *MyDir* 
$ git clone --depth=1 https://github.com/Qengineering/YoloV8-TensorRT-Jetson_Nano.git
You need your "trtexec" app on your Jetson to convert the model from onnx to the engine format. Usually, "trtexec" is found in the 
/usr/src/tensorrt/bin/
folder on your Jetson.
$ trtexec --onnx=yolov8s.onnx --saveEngine=yolov8s.engine --fp16
$ cd *MyDir*$ mkdir build$ cd build$ cmake ..$ make -j4 

Finally you can use the following command to run the demo ./YoloV8rt model/yolov8s.engine [image or video path]
