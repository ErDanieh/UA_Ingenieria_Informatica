cmake_minimum_required(VERSION 3.15)
project(cross-validation)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
find_package(OpenMP)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
include_directories(${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
add_executable(cv main.cc crossValidation.cc mnist.cc knn.cc sample.cc)
target_link_libraries(cv ${OpenCV_LIBS})
