cmake_minimum_required(VERSION 3.15)

find_package(pybind11 REQUIRED)
pybind11_add_module(sciurus_robot sciurus_robot.cpp)
install(TARGETS sciurus_robot LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
