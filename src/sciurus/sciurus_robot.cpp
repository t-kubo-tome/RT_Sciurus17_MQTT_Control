#include <stdexcept>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "rt_manipulators_cpp/hardware.hpp"
#include "sciurus_robot.hpp"

Robot::Robot(const std::string & port_name): hardware_(port_name) {
}
Robot::~Robot() {
  disable();
  disconnect();
}
void Robot::connect(int baudrate) {
  if (!hardware_.connect(baudrate)) {
    throw std::runtime_error("ロボットとの接続に失敗しました.");
  }
  std::string config_file = "config/sciurus17.yaml";
  if (!hardware_.load_config_file(config_file)) {
    throw std::runtime_error("コンフィグファイルの読み込みに失敗しました.");
  }
} 
void Robot::disconnect() {
  hardware_.disconnect();
}
void Robot::enable() {}
void Robot::disable() {}
void Robot::move_joint(std::vector<double> joints) {}
std::vector<double> Robot::get_current_joint() {
  std::vector<double> ret;
  return ret;
}
void Robot::enter_servo_mode() {}
void Robot::leave_servo_mode() {}
void Robot::move_joint_servo(std::vector<double> joints) {}
std::vector<double> Robot::get_current_joint_servo() {
  std::vector<double> ret;
  return ret;
}

namespace py = pybind11;

PYBIND11_MODULE(sciurus_robot, m)
{
    m.doc() = "pybind11 example plugin";

    py::class_<Robot>(m, "SciurusRobot")
        .def(py::init<const std::string &>(),
             py::arg("ip") = "192.168.5.43")
        .def("connect", &Robot::connect)
        .def("disconnect", &Robot::disconnect);
        .def("enable", &Robot::enable)
        .def("disable", &Robot::disable)
        .def("move_joint", &Robot::move_joint)
        .def("get_current_joint", &Robot::get_current_joint)
        .def("enter_servo_mode", &Robot::enter_servo_mode)
        .def("leave_servo_mode", &Robot::leave_servo_mode)
        .def("move_joint_servo", &Robot::move_joint_servo)
        .def("get_current_joint_servo", &Robot::get_current_joint_servo);
}
