set(TARGET img-proc)

find_package(OpenCV CONFIG REQUIRED PATHS "../addons/opencv/build") 


set(SOURCES
	kernel.cpp
	image.cpp 
	main.cpp)

add_executable(${TARGET} ${SOURCES}) 

target_link_directories(${TARGET} PUBLIC
    ${OpenCV_LIB_DIRS}
    )
target_link_libraries(${TARGET}
    ${OpenCV_LIBS}
    )
target_include_directories(${TARGET} PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    )