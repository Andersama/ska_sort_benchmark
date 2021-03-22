# CMakeList.txt : CMake project for ska_test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ska_test "ska_test.cpp" "ska_test.h" "ska_sort.h" "nanobench.h")

# TODO: Add tests and install targets if needed.
