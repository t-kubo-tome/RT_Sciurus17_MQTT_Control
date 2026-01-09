#pragma once
#include <string>
#include <vector>

#include "rt_manipulators_cpp/hardware.hpp"


class Robot
{
public:
  Robot(const std::string & port_name = "/dev/ttyUSB0");
  ~Robot();
  void connect(int baudrate = 3000000);
  void disconnect();
  void enable();
  void disable();
  void move_joint(std::vector<double> joints);
  std::vector<double> get_current_joint();
  void enter_servo_mode();
  void leave_servo_mode();
  void move_joint_servo(std::vector<double> joints);
  std::vector<double> get_current_joint_servo();
private:
  rt_manipulators_cpp::Hardware hardware_;
};
