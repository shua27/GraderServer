# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (CppSkeleton)

add_executable(submission main.cpp)
target_link_libraries(submission ${CPR_LIBRARIES})
