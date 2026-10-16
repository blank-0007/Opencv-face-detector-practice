<div align="center">

# 👁️ Real-Time C++ Face Detector

### *High-performance computer vision application powered by OpenCV & Haar Cascades*

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![OpenCV](https://img.shields.io/badge/OpenCV-5.x%20%7C%204.x-5C3EE8?style=for-the-badge&logo=opencv&logoColor=white)](https://opencv.org/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![macOS](https://img.shields.io/badge/macOS-AVFoundation-000000?style=for-the-badge&logo=apple&logoColor=white)](https://apple.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

<p align="center">
  <b>Detects human faces in real-time through live webcam feeds with sub-30ms latency, multi-face tracking, and bounding box visualizations.</b>
</p>

---

</div>

## 📌 Overview

This project is a standalone C++ computer vision application implementing the **Viola-Jones object detection framework** using pre-trained **Haar Feature-based Cascade Classifiers**. Built with modern C++17 and compiled against OpenCV, it interfaces directly with hardware video capture devices using Apple's native **AVFoundation** framework on macOS.

---

## ⚡ Architecture & Pipeline

```text
  ┌───────────────┐
  │  Live Webcam  │  (Native AVFoundation Video Capture)
  └───────┬───────┘
          │  BGR Frame (1080p / 720p)
          ▼
  ┌───────────────┐
  │ Color Convert │  cv::cvtColor(..., cv::COLOR_BGR2GRAY)
  └───────┬───────┘
          │  Single-Channel Grayscale
          ▼
  ┌───────────────┐
  │ Hist Equalize │  cv::equalizeHist(...) [Normalizes Lighting & Contrast]
  └───────┬───────┘
          │  High-Contrast Matrix
          ▼
  ┌───────────────┐
  │ Haar Cascade  │  faceCascade.detectMultiScale(scaleFactor=1.2, minNeighbors=5)
  └───────┬───────┘
          │  std::vector<cv::Rect> [Bounding Coordinates]
          ▼
  ┌───────────────┐
  │ Visual Overlay│  cv::rectangle() + cv::putText() + Counter HUD
  └───────┬───────┘
          │
          ▼
     Live Window Display
```

---

## ✨ Key Features

| Feature | Description |
| :--- | :--- |
| 🎯 **Real-Time Detection** | Detects single and multiple faces concurrently at 30+ FPS. |
| 🎛️ **Lighting Normalization** | Uses histogram equalization to ensure consistent detection across bright and dim lighting. |
| 🍎 **macOS Native Capture** | Targets `cv::CAP_AVFOUNDATION` directly for smooth camera integration. |
| 🛡️ **Fault-Tolerant Fallback** | Seamlessly falls back to local test images (`blank.jpeg`) if camera permissions are unavailable. |
| 📊 **On-Screen HUD** | Overlays real-time detection counts and target bounding boxes directly onto the frame. |

---

## 📂 Project Structure

```text
opencv-face-detector/
├── CMakeLists.txt                       # Build system configuration
├── README.md                            # Documentation
├── face_detect.cpp                      # Main application source code
├── haarcascade_frontalface_default.xml  # Pre-trained Haar Cascade model weights
└── .gitignore                           # Git ignore rules (build artifacts)
```

---

## 🚀 Getting Started

### Prerequisites

Ensure you have a C++17 compiler, CMake, and OpenCV installed:

```bash
# macOS (using Homebrew)
brew install cmake opencv
```

### Build the Project

```bash
# 1. Clone the repository
git clone https://github.com/blank-0007/Opencv-face-detector-practice.git
cd Opencv-face-detector-practice

# 2. Configure build files
cmake -B build

# 3. Compile the executable
cmake --build build
```

### Run the Face Detector

```bash
./build/face_detector
```

> **Note for macOS Users:** On first run, click **OK** when macOS prompts to grant camera access to your terminal.

---

## 🎮 Controls & Keybindings

| Key | Action |
| :---: | :--- |
| **`q`** | Exit the application |
| **`ESC`** | Terminate detection window |

---

## 🔬 How It Works (Behind the Scenes)

* **Haar-like Features:** The classifier evaluates adjacent rectangular regions at a specific location in a detection window, calculates pixel sum differences, and categorizes facial features (e.g., eye sockets are darker than cheeks).
* **Integral Images:** Calculates pixel sums in constant $O(1)$ time regardless of rectangle size, enabling rapid multi-scale feature evaluation.
* **Cascading:** Stages of weak classifiers quickly reject non-face regions (backgrounds) in early stages, focusing compute only on candidate face regions.

---

## 📚 Acknowledgments & References

* Built based on concepts from [Murtaza's Workshop - Learn OpenCV C++](https://youtu.be/2FYm3GOonhk).
* Powered by the [OpenCV Open Source Computer Vision Library](https://opencv.org/).
* Pre-trained weights from the official [OpenCV Haar Cascades Repository](https://github.com/opencv/opencv/tree/master/data/haarcascades).

---

<div align="center">
  <sub>Created with modern C++ & OpenCV by <a href="https://github.com/blank-0007">Kaushal</a></sub>
</div>
