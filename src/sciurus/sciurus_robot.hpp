#pragma once
#include <string>
#include <vector>

class Robot
{
public:
  Robot(const std::string & ip = "192.168.5.43");
  ~Robot();
  bool connect();
  bool enable();
  bool move_joint(float j1, float j2, float j3, float j4, float j5, float j6);
  std::vector<double> get_current_joint();
  bool disable();
  bool disconnect();
private:
  std::string ip_;
};
