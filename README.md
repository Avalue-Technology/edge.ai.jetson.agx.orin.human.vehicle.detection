# YOLOv8 TensorRT Human and Vehicle Detection on Jetson AGX Orin

This guide outlines the steps to run human and vehicle detection using YOLOv8 and TensorRT on the NVIDIA Jetson AGX Orin.

## Prerequisites

1.  **Update and Upgrade System Packages:**
    ```bash
    sudo apt-get update
    sudo apt-get upgrade
    ```

2.  **Install Necessary Tools:**
    ```bash
    sudo apt-get install cmake wget curl
    ```

## Code Acquisition and Building

1.  **Create a Working Directory (replace `MyDir` with your desired directory name):**
    ```bash
    mkdir MyDir
    cd MyDir
    ```

2.  **Clone the YoloV8-TensorRT-Jetson_Nano Repository:**
    ```bash
    git clone --depth=1 [https://github.com/Qengineering/YoloV8-TensorRT-Jetson_Nano.git](https://github.com/Qengineering/YoloV8-TensorRT-Jetson_Nano.git)
    ```

3.  **Locate the `trtexec` Application:**
    The `trtexec` tool is typically found in the `/usr/src/tensorrt/bin/` folder on your Jetson. This tool is used to convert the ONNX model to the TensorRT engine format.

4.  **Convert ONNX Model to TensorRT Engine (assuming you have an ONNX model named `yolov8s.onnx`):**
    ```bash
    trtexec --onnx=yolov8s.onnx --saveEngine=yolov8s.engine --fp16
    ```
    **Note:** You might need to replace `yolov8s.onnx` with the actual path to your ONNX model.

5.  **Create a Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

6.  **Configure the Build with CMake:**
    ```bash
    cmake ..
    ```

7.  **Compile the Project:**
    ```bash
    make -j4
    ```

## Running the Demo

After compilation, you can use the following command to run the human and vehicle detection demo:

```bash
./YoloV8rt model/yolov8s.engine [image or video path]
