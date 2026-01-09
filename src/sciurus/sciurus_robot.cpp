#include <stdexcept>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "rt_manipulators_cpp/hardware.hpp"
#include "sciurus_robot.hpp"

std::vector<double> slice(const std::vector<double>& v, size_t start, size_t end) {
  return std::vector<double>(v.begin() + start, v.begin() + end);
}

Robot::Robot(const std::string & port_name, int t_samp): hardware(port_name), t_samp(t_samp) {
}
Robot::~Robot() {
  disable();
  disconnect();
}
void Robot::connect(int baudrate) {
  if (!hardware.connect(baudrate)) {
    throw std::runtime_error("ロボットとの接続に失敗しました.");
  }
  std::string config_file = "config/sciurus17.yaml";
  if (!hardware.load_config_file(config_file)) {
    throw std::runtime_error("コンフィグファイルの読み込みに失敗しました.");
  }
  if (!hardware.write_max_acceleration_to_group("right_arm", 0.5 * M_PI)) {
    std::cerr << "right_armグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("right_arm", 0.5 * M_PI)) {
    std::cerr << "right_armグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("right_hand", 0.5 * M_PI)) {
    std::cerr << "right_handグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("right_hand", 0.5 * M_PI)) {
    std::cerr << "right_handグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("left_arm", 0.5 * M_PI)) {
    std::cerr << "left_armグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("left_arm", 0.5 * M_PI)) {
    std::cerr << "left_armグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("left_hand", 0.5 * M_PI)) {
    std::cerr << "left_handグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("left_hand", 0.5 * M_PI)) {
    std::cerr << "left_handグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("torso", 0.5 * M_PI)) {
    std::cerr << "torsoグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("torso", 0.5 * M_PI)) {
    std::cerr << "torsoグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }

  if (!hardware.write_position_pid_gain_to_group("right_arm", 800, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 800, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 800, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 800, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 800, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
} 
void Robot::disconnect() {
  hardware.disconnect();
}
void Robot::enable() {
  if (!hardware.torque_on("right_arm")) {
    std::cerr << "right_armグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("right_hand")) {
    std::cerr << "right_handグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("left_arm")) {
    std::cerr << "left_armグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("left_hand")) {
    std::cerr << "left_handグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("torso")) {
    std::cerr << "torsoグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
}
void Robot::disable() {
  if (!hardware.write_position_pid_gain_to_group("right_arm", 5, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 5, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 5, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 5, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 5, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  std::this_thread::sleep_for(std::chrono::seconds(5));

  if (!hardware.torque_off("right_arm")) {
    std::cerr << "right_armグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("right_hand")) {
    std::cerr << "right_handグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("left_arm")) {
    std::cerr << "left_armグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("left_hand")) {
    std::cerr << "left_handグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("torso")) {
    std::cerr << "torsoグループのトルクをOFFできませんでした." << std::endl;
  }

  if (!hardware.write_position_pid_gain_to_group("right_arm", 800, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 800, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 800, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 800, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 800, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
void Robot::move_joint(std::vector<double> joints, int timeout) {
  auto right_arm = slice(joints, 0, 7);
  auto right_hand = slice(joints, 7, 8);
  auto left_arm = slice(joints, 8, 15);
  auto left_hand = slice(joints, 15, 16);
  auto torso = slice(joints, 16, 19);
  hardware.set_positions("right_arm", right_arm);
  hardware.set_positions("right_hand", right_hand);
  hardware.set_positions("left_arm", left_arm);
  hardware.set_positions("left_hand", left_hand);
  hardware.set_positions("torso", torso);
  if (!hardware.sync_write("right_arm")) {
    std::cerr << "right_armグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("right_hand")) {
    std::cerr << "right_handグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("left_arm")) {
    std::cerr << "left_armグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("left_hand")) {
    std::cerr << "left_handグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("torso")) {
    std::cerr << "torsoグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  std::this_thread::sleep_for(std::chrono::seconds(timeout));
}
std::vector<double> Robot::get_current_joint() {
  std::vector<double> ret;
  if (!hardware.sync_read("right_arm")) {
    std::cerr << "right_armグループのsync readに失敗しました." << std::endl;
    break;
  }
  if (!hardware.sync_read("right_hand")) {
    std::cerr << "right_handグループのsync readに失敗しました." << std::endl;
    break;
  }
  if (!hardware.sync_read("left_arm")) {
    std::cerr << "left_armグループのsync readに失敗しました." << std::endl;
    break;
  }
  if (!hardware.sync_read("left_hand")) {
    std::cerr << "left_handグループのsync readに失敗しました." << std::endl;
    break;
  }
  if (!hardware.sync_read("torso")) {
    std::cerr << "torsoグループのsync readに失敗しました." << std::endl;
    break;
  }
  std::vector<double> right_arm_positions;
  if (!hardware.get_positions("right_arm", right_arm_positions)) {
    std::cerr << "right_armグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> right_hand_positions;
  if (!hardware.get_positions("right_hand", right_hand_positions)) {
    std::cerr << "right_handグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> left_arm_positions;
  if (!hardware.get_positions("left_arm", left_arm_positions)) {
    std::cerr << "left_armグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> left_hand_positions;
  if (!hardware.get_positions("left_hand", left_hand_positions)) {
    std::cerr << "left_handグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> torso_positions;
  if (!hardware.get_positions("torso", torso_positions)) {
    std::cerr << "torsoグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  ret.insert(ret.end(), right_arm_positions.begin(), right_arm_positions.end());
  ret.insert(ret.end(), right_hand_positions.begin(), right_hand_positions.end());
  ret.insert(ret.end(), left_arm_positions.begin(), left_arm_positions.end());
  ret.insert(ret.end(), left_hand_positions.begin(), left_hand_positions.end());
  ret.insert(ret.end(), torso_positions.begin(), torso_positions.end());
  return ret;
}
void Robot::enter_servo_mode() {
  std::vector<std::string> group_names = {
      "right_arm", "right_hand", "left_arm", "left_hand", "torso"};
  if (!hardware.start_thread(group_names, std::chrono::milliseconds(t_samp))) {
    std::cerr << "スレッドの起動に失敗しました." << std::endl;
    return -1;
  }
}
void Robot::leave_servo_mode() {
  hardware.stop_thread();
}
void Robot::move_joint_servo(std::vector<double> joints) {
  auto right_arm = slice(joints, 0, 7);
  auto right_hand = slice(joints, 7, 8);
  auto left_arm = slice(joints, 8, 15);
  auto left_hand = slice(joints, 15, 16);
  auto torso = slice(joints, 16, 19);
  hardware.set_positions("right_arm", right_arm);
  hardware.set_positions("right_hand", right_hand);
  hardware.set_positions("left_arm", left_arm);
  hardware.set_positions("left_hand", left_hand);
  hardware.set_positions("torso", torso);
}
std::vector<double> Robot::get_current_joint_servo() {
  std::vector<double> ret;
  std::vector<double> right_arm_positions;
  if (!hardware.get_positions("right_arm", right_arm_positions)) {
    std::cerr << "right_armグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> right_hand_positions;
  if (!hardware.get_positions("right_hand", right_hand_positions)) {
    std::cerr << "right_handグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> left_arm_positions;
  if (!hardware.get_positions("left_arm", left_arm_positions)) {
    std::cerr << "left_armグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> left_hand_positions;
  if (!hardware.get_positions("left_hand", left_hand_positions)) {
    std::cerr << "left_handグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  std::vector<double> torso_positions;
  if (!hardware.get_positions("torso", torso_positions)) {
    std::cerr << "torsoグループのサーボ角度の取得に失敗しました." << std::endl;
    break;
  }
  ret.insert(ret.end(), right_arm_positions.begin(), right_arm_positions.end());
  ret.insert(ret.end(), right_hand_positions.begin(), right_hand_positions.end());
  ret.insert(ret.end(), left_arm_positions.begin(), left_arm_positions.end());
  ret.insert(ret.end(), left_hand_positions.begin(), left_hand_positions.end());
  ret.insert(ret.end(), torso_positions.begin(), torso_positions.end());
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
