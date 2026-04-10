cmake_minimum_required(VERSION 3.10)

project(ImgProc)

set(CMAKE_CXX_STANDARD 11)

set(OPENCV_EXTRA_MODULES_PATH "${CMAKE_SOURCE_DIR}/addons/opencv_contrib/modules" CACHE PATH "")

add_executable(ImgProc
    src/main.cpp
    src/image.cpp
    src/kernel.cpp
)

# if(WIN32)
    # set(SCRIPT_CMD cmd /c ${CMAKE_CURRENT_SOURCE_DIR}/b-n-i-opencv.bat)
# else()
    # set(SCRIPT_CMD /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/b-n-i-opencv.sh)
# endif()

# execute_process(
    # COMMAND ${SCRIPT_CMD}
    # RESULT_VARIABLE SCRIPT_RESULT
    # OUTPUT_VARIABLE SCRIPT_OUTPUT
	# REQUIRED
# )

target_link_libraries(ImgProc
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
)

set(OpenCV_DIR addons/build-opencv)

find_package(OpenCV REQUIRED)

if(OpenCV_CXX_FOUND)
    target_link_libraries(ImgProc ${OpenCV_CXX_LIBRARIES})
    target_compile_options(ImgProc PRIVATE ${OpenCV_CXX_FLAGS})
endif()


find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ImgProc ${OpenMP_CXX_LIBRARIES})
    target_compile_options(ImgProc PRIVATE ${OpenMP_CXX_FLAGS})
endif()