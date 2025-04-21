#!/bin/bash
# My custom startup script


# Add any other startup commands here
/home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/YoloV8rt /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/models/yolov8n.engine /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/car.mp4 0 0 &
/home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/YoloV8rt /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/models/yolov8n.engine /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/human.mp4 0 540 &
/home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/YoloV8rt /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/models/yolov8n.engine /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/human.mp4 960 0 &
/home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/YoloV8rt /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/models/yolov8n.engine /home/user/Downloads/CarDetection/YoloV8-TensorRT-Jetson_Nano/car.mp4 960 540

