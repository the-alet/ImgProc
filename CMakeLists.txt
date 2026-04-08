cmake_minimum_required(VERSION 3.10)

project(ImgProc)

set(CMAKE_CXX_STANDARD 11)


set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)

set(BUILD_opencv_core ON)
set(BUILD_opencv_imgproc ON)
set(BUILD_opencv_imgcodecs ON)

set(BUILD_opencv_calib3d OFF)
set(BUILD_opencv_dnn OFF)
set(BUILD_opencv_features2d OFF)
set(BUILD_opencv_flann OFF)
set(BUILD_opencv_gapi OFF)
set(BUILD_opencv_highgui OFF)
set(BUILD_opencv_ml OFF)
set(BUILD_opencv_objdetect OFF)
set(BUILD_opencv_photo OFF)
set(BUILD_opencv_stitching OFF)
set(BUILD_opencv_video OFF)
set(BUILD_opencv_videoio OFF)

set(OPENCV_EXTRA_MODULES_PATH "${CMAKE_SOURCE_DIR}/addons/opencv_contrib/modules" CACHE PATH "")

add_subdirectory(addons/opencv)

add_executable(ImgProc
    src/main.cpp
    src/image.cpp
    src/kernel.cpp
)

target_link_libraries(ImgProc
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(ImgProc ${OpenMP_CXX_LIBRARIES})
    target_compile_options(ImgProc PRIVATE ${OpenMP_CXX_FLAGS})
endif()