cmake_minimum_required(VERSION 3.16)
project(OpenCVFaceDetector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(face_detector face_detect.cpp)
target_link_libraries(face_detector ${OpenCV_LIBS})
