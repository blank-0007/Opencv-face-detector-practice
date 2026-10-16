# Real-Time C++ Face Detector (OpenCV)

A lightweight real-time face detection application built in C++ using OpenCV and Haar Feature-based Cascade Classifiers (`haarcascade_frontalface_default.xml`).

## Features
- Real-time webcam face tracking with bounding boxes and detection counts.
- Preprocessed using grayscale conversion and histogram equalization.
- Image fallback support when no live camera feed is detected.

## Prerequisites
- macOS or Linux
- CMake (>= 3.16)
- Modern C++ compiler (C++17)
- OpenCV (installed via Homebrew: `brew install opencv`)

## Build & Run

```bash
# Configure and build
cmake -B build
cmake --build build

# Run the face detector
./build/face_detector
```
Press `q` or `ESC` to quit the application.
