#include <iostream>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/xobjdetect.hpp>

int main() {
    // 1. Load the pre-trained Haar Cascade XML
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error: Could not load haarcascade_frontalface_default.xml!" << std::endl;
        return -1;
    }

    // 2. Open camera using AVFoundation backend explicitly
    cv::VideoCapture cap;
    
    // Try device index 0, then 1 (in case Continuity camera takes index 0)
    std::cout << "Connecting to camera via AVFoundation..." << std::endl;
    cap.open(0, cv::CAP_AVFOUNDATION);
    if (!cap.isOpened()) {
        cap.open(1, cv::CAP_AVFOUNDATION);
    }

    // If macOS permission prompt just appeared, give it 1 second to initialize
    if (!cap.isOpened()) {
        std::cout << "Waiting for camera authorization..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
        cap.open(0, cv::CAP_AVFOUNDATION);
        if (!cap.isOpened()) {
            cap.open(1, cv::CAP_AVFOUNDATION);
        }
    }

    if (!cap.isOpened()) {
        std::cerr << "\nCould not access the live webcam." << std::endl;
        std::cerr << "Testing on image 'blank.jpeg' instead..." << std::endl;

        cv::Mat frame = cv::imread("blank.jpeg");
        if (frame.empty()) {
            std::cerr << "Could not open blank.jpeg" << std::endl;
            return -1;
        }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 4, 0, cv::Size(30, 30));

        for (const auto& face : faces) {
            cv::rectangle(frame, face.tl(), face.br(), cv::Scalar(255, 0, 255), 3);
            cv::putText(frame, "Face", cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 255), 2);
        }

        cv::imshow("Face Detection (Image Fallback)", frame);
        std::cout << "Faces found in image: " << faces.size() << ". Press any key to exit." << std::endl;
        cv::waitKey(0);
        return 0;
    }

    cv::Mat frame, gray;
    std::cout << "Face Detection Running. Look into the camera. Press 'q' or 'ESC' to exit." << std::endl;

    while (true) {
        cap.read(frame);
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(
            gray,
            faces,
            1.2,
            5,
            0,
            cv::Size(60, 60)
        );

        for (const auto& face : faces) {
            cv::rectangle(frame, face.tl(), face.br(), cv::Scalar(255, 0, 255), 3);
            cv::putText(frame, "Face", cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 255), 2);
        }

        std::string countText = "Faces detected: " + std::to_string(faces.size());
        cv::putText(frame, countText, cv::Point(20, 40),
                    cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        cv::imshow("Murtaza's Course - Face Detection", frame);

        char key = static_cast<char>(cv::waitKey(20));
        if (key == 'q' || key == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
