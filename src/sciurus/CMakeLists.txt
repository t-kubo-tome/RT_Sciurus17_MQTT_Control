cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(pybind11 REQUIRED)
pybind11_add_module(sciurus_robot sciurus_robot.cpp)
target_link_libraries(sciurus_robot PRIVATE rt_manipulators_cpp)
install(TARGETS sciurus_robot LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
