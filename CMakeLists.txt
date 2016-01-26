cmake_minimum_required(VERSION 2.6)
project(BinarySearchTreeStorage)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(${PROJECT_NAME}_VERSION_MAJOR_0)
set(${PROJECT_NAME}_VERSION_MINOR_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  include)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/bsts/BinaryTree.cpp
  src/bsts/BinarySearchTree.cpp)
