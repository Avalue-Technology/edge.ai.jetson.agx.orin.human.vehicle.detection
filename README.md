# Jetson AGX Orin 上的 YOLOv8 TensorRT 人員與車輛偵測範例

本指南說明如何在 NVIDIA Jetson AGX Orin 上使用 YOLOv8 和 TensorRT 執行人員與車輛偵測。

## 環境準備

1.  **更新和升級系統套件：**
    ```bash
    sudo apt-get update
    sudo apt-get upgrade
    ```

2.  **安裝必要的工具：**
    ```bash
    sudo apt-get install cmake wget curl
    ```

## 程式碼取得與建置

1.  **建立工作目錄 (請將 `MyDir` 替換為您想要的目錄名稱)：**
    ```bash
    mkdir MyDir
    cd MyDir
    ```

2.  **克隆 YOLOv8-TensorRT-Jetson_Nano 儲存庫：**
    ```bash
    git clone --depth=1 [https://github.com/Qengineering/YoloV8-TensorRT-Jetson_Nano.git](https://github.com/Qengineering/YoloV8-TensorRT-Jetson_Nano.git)
    ```

3.  **尋找 `trtexec` 應用程式：**
    `trtexec` 工具通常位於 Jetson 上的 `/usr/src/tensorrt/bin/` 資料夾中。此工具用於將 ONNX 模型轉換為 TensorRT 引擎格式。

4.  **轉換 ONNX 模型至 TensorRT 引擎 (假設您有名為 `yolov8s.onnx` 的 ONNX 模型)：**
    ```bash
    trtexec --onnx=yolov8s.onnx --saveEngine=yolov8s.engine --fp16
    ```
    **注意：** 您可能需要將 `yolov8s.onnx` 替換為您實際使用的 ONNX 模型路徑。

5.  **建立建置目錄：**
    ```bash
    mkdir build
    cd build
    ```

6.  **使用 CMake 配置建置：**
    ```bash
    cmake ..
    ```

7.  **編譯專案：**
    ```bash
    make -j4
    ```

## 執行範例

編譯完成後，您可以使用以下命令來執行人員與車輛偵測的範例：

```bash
./YoloV8rt model/yolov8s.engine [圖片或影片路徑]
