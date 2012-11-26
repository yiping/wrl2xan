# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)
 
project(wrl2xan)

find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS}) 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})


add_executable(readlabel_test  readlabel_test.cpp)
add_executable(scanwrl_test  scanwrl_test.cpp)
add_executable(strtok_test  strtok_test.cpp)


set(SRCS wrl2xan_batch.cpp
		 functions.cpp)
add_executable(wrl2xan  ${SRCS})
