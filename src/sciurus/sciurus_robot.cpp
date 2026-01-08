#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "sciurus_robot.hpp"

Robot::Robot(const std::string & ip): ip_(ip) {   
}
Robot::~Robot() {
  disable();
  disconnect();
}
bool Robot::connect() {
    return true;
} 
bool Robot::enable() {
  return true;
}
bool Robot::move_joint(float j1, float j2, float j3, float j4, float j5, float j6) {
  return true;
}
std::vector<double> Robot::get_current_joint() {
  std::vector<double> ret;
  return ret;
}
bool Robot::disable() {
  return true;
}
bool Robot::disconnect() {
  return true;
}

namespace py = pybind11;

PYBIND11_MODULE(sciurus_robot, m)
{
    m.doc() = "pybind11 example plugin";

    py::class_<Robot>(m, "SciurusRobot")
        .def(py::init<const std::string &>(),
             py::arg("ip") = "192.168.5.43")
        .def("connect", &Robot::connect)
        .def("enable", &Robot::enable)
        .def("move_joint", &Robot::move_joint)
        .def("get_current_joint", &Robot::get_current_joint)
        .def("disable", &Robot::disable)
        .def("disconnect", &Robot::disconnect);
}
